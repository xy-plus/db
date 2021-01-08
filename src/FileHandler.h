#pragma once

#include "Record.h"
#include "PageInfo.h"

class BufPageManager;
typedef unsigned int* BufType;

class FileHandler {
private:
    MetadataPageInfo* metadata;  // 元数据页
    int metadata_index;          // 元数据在文件系统中的页号
    BufPageManager* bpm;         // 文件对应的缓冲区
    int fileID;                  // 文件 id
	bool isOpened;

public:
	FileHandler();
    FileHandler(BufPageManager* bpm_, int fileID_);

	int getFileID() const ;

    /* 获取一个页面的首地址
     * 如果有读/写操作，不要忘记通过设置
     * bpm->markDirty(index) 或 bpm->access(index)
     */
    BufType getPage(int pageID, int& index) const;

    // 通过 id 找 record
    bool getRecordById(RecordID rid, Record& rec) const;

    // 删除一条记录
    bool deleteRecord(RecordID rid);

    // 插入一条 record
    RecordID insertRecord(BufType record);

    /* 返回符合条件(check retrun true)的结果数量
     * 结果放到 result 中
     * result 需要提前分配好内存
     */
    int selectRecord(Record* result, bool (*check)(Record&));

    bool modifyRecord(RecordID rid, BufType record);

	bool isOpen() const;

	void release();

	int getPageNumber() const;

	int getSlotNumber() const;
};
