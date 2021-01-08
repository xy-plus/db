#pragma once

typedef unsigned int uint;

// 文件的第一页要存放元数据
struct MetadataPageInfo {
    uint nextAvailPage;
    uint pageCount;
    uint recordLength;
    uint recordCount;
    uint pageSlotNumber;

    void print();
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
    int getNextAvailSlot();

    // 检察这个位置是否已经被使用
    bool checkSlot(int slot);

    void setSlot(int slot);

    void resetSlot(int slot);
};
