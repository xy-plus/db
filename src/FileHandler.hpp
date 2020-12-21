#ifndef FILE_HANDLER_HPP
#define FILE_HANDLER_HPP

#include "../filesystem/bufmanager/BufPageManager.h"
#include "PageInfo.hpp"
#include "Record.hpp"

class FileHandler {
private:
    MetadataPageInfo* metadata;  // 元数据页
    int metadata_index;          // 元数据在文件系统中的页号
    BufPageManager* bpm;         // 文件对应的缓冲区
    int fileID;                  // 文件 id
	bool isOpened;

public:
	FileHandler(): isOpened(false){}
    FileHandler(BufPageManager* bpm_, int fileID_)
        : bpm(bpm_), fileID(fileID_) {
        metadata = (MetadataPageInfo*)bpm->getPage(
            fileID, 0, metadata_index);  // 默认第0页是 metadata
        bpm->access(metadata_index);
    }

	int getFileID() const { return fileID; }

    /* 获取一个页面的首地址
     * 如果有读/写操作，不要忘记通过设置
     * bpm->markDirty(index) 或 bpm->access(index)
     */
    BufType getPage(int pageID, int& index) const {
        return bpm->getPage(fileID, pageID, index);
    }

    // 通过 id 找 record
    bool getRecordById(RecordID rid, Record& rec) const {
        int index;
        PageInfo* pg = (PageInfo*)getPage(rid.page, index);
        if (pg->checkSlot(rid.slot)) {
            rec.assign(Record(pg->data + rid.slot * metadata->recordLength,
                              metadata->recordLength, rid));
            bpm->access(index);
            return true;
        } else {
            return false;
        }
    }

    // 删除一条记录
    bool deleteRecord(RecordID rid) {
        Record rec;
        if (!getRecordById(rid, rec))
            return false;
        int index;
        PageInfo* pg = (PageInfo*)getPage(rid.page, index);
        pg->resetSlot(rid.slot);
        bpm->markDirty(index);
        if (pg->pageNumber != metadata->nextAvailPage) {
            pg->nextAvailPage = metadata->nextAvailPage;
            metadata->nextAvailPage = pg->pageNumber;
            bpm->markDirty(metadata_index);
        }
        return true;
    }

    // 插入一条 record
    RecordID insertRecord(BufType record) {
        int pageIndex = metadata->nextAvailPage, index;
        PageInfo* pg = (PageInfo*)getPage(pageIndex, index);
        int availSlot = pg->getNextAvailSlot();
		int allocPage = metadata->nextAvailPage;
		int allocSlot = availSlot;
        memcpy(pg->data + metadata->recordLength * availSlot, record,
               metadata->recordLength * sizeof(uint));
        pg->setSlot(availSlot);
        bpm->markDirty(index);
        ++metadata->recordCount;
        bpm->markDirty(metadata_index);
        // 如果当前页面已经没有空位
        if (pg->getNextAvailSlot() >= metadata->pageSlotNumber) {
            // 如果所有已分配的页面都已经使用，则通过文件系统进行页面分配
            if (pg->nextAvailPage == 0) {
                PageInfo* new_pg = (PageInfo*)bpm->allocPage(
                    fileID, metadata->pageCount, index);
                bpm->markDirty(index);
                metadata->nextAvailPage = new_pg->pageNumber =
                    metadata->pageCount++;
                new_pg->nextAvailPage = 0;
				for (int i = 0; i < 62; ++i)
					new_pg->bitmap[i] = 0u;
            } else
                metadata->nextAvailPage = pg->nextAvailPage;
        }
		return RecordID(allocPage, allocSlot);
    }

    /* 返回符合条件(check retrun true)的结果数量
     * 结果放到 result 中
     * result 需要提前分配好内存
     */
    int selectRecord(Record* result, bool (*check)(Record&)) {
        int cnt = 0, index;
        for (int i = 1; i < metadata->pageCount; ++i) {
            PageInfo* pg = (PageInfo*)getPage(i, index);
            bpm->access(index);
            for (int j = 0; j < metadata->pageSlotNumber; ++j) {
                if (pg->checkSlot(j)) {
                    Record rec = Record(pg->data + metadata->recordLength * j,
                                        metadata->recordLength, RecordID(i, j));
                    if (check(rec))
                        result[cnt++].assign(rec);
                }
            }
        }
        return cnt;
    }

    bool modifyRecord(RecordID rid, BufType record) {
        Record rec;
        if (getRecordById(rid, rec)) {
            int index;
            PageInfo* pg = (PageInfo*)getPage(rid.page, index);
            memcpy(pg->data + metadata->recordLength * rid.slot, record,
                   metadata->recordLength * sizeof(uint));
            bpm->markDirty(index);
            return true;
        } else {
            return false;
        }
    }

	bool isOpen() const { return isOpened; }

	void release() {
		isOpened = false;
	}

	int getPageNumber() const { return metadata->pageCount; }

	int getSlotNumber() const { return metadata->pageSlotNumber; }
};

#endif