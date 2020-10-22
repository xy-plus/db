#ifndef PAGE_INFO_HPP
#define PAGE_INFO_HPP

#include <iostream>
#include "../filesystem/utils/pagedef.h"
using namespace std;

// 文件的第一页要存放元数据
struct MetadataPageInfo {
    uint nextAvailPage;
    uint pageCount;
    uint recordLength;
    uint recordCount;
    uint pageSlotNumber;

    void print() {
        cout << "NextAvailPage = " << nextAvailPage << endl;
        cout << "PageCount = " << pageCount << endl;
        cout << "RecordLength = " << recordLength << endl;
        cout << "RecordCount = " << recordCount << endl;
        cout << "PageSlotNumber = " << pageSlotNumber << endl;
    }
};

/* 提供的 filesystem 每次分配的页面大小为 8kb
 * 折合为 2048 个 uint
 * nextAvailPage 和 pageNumber 用两个
 * bitmap 和 data 共 2046 个
 * 1984 + 62 == 2046
 * 1984 == 62 * sizeof(uint) * 8
 */
const uint PAGE_SLOT_COUNT = 1984;
struct PageInfo {
    uint nextAvailPage;
    uint pageNumber;
    uint bitmap[62];
    uint data[PAGE_SLOT_COUNT];

    // 查找下一个可用的位置
    int getNextAvailSlot() {
        for (uint i = 0; i < PAGE_SLOT_COUNT; ++i)
            if (!checkSlot(i))
                return i;
        return 0;
    }

    // 检察这个位置是否已经被使用
    bool checkSlot(int slot) {
        return bitmap[slot >> 5] & (1u << (slot & 0x1f));
    }

    void setSlot(int slot) { bitmap[slot >> 5] |= (1u << (slot & 0x1f)); }

    void resetSlot(int slot) { bitmap[slot >> 5] &= ~(1u << (slot & 0x1f)); }
};

#endif
