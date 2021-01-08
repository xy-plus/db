#include <iostream>
#include "PageInfo.h"
using namespace std;


void MetadataPageInfo::print() {
    cout << "NextAvailPage = " << nextAvailPage << endl;
    cout << "PageCount = " << pageCount << endl;
    cout << "RecordLength = " << recordLength << endl;
    cout << "RecordCount = " << recordCount << endl;
    cout << "PageSlotNumber = " << pageSlotNumber << endl;
}

int PageInfo::getNextAvailSlot() {
    for (uint i = 0; i < PAGE_SLOT_COUNT; ++i)
        if (!checkSlot(i))
            return i;
    return 0;
}

// 检察这个位置是否已经被使用
bool PageInfo::checkSlot(int slot) {
    return bitmap[slot >> 5] & (1u << (slot & 0x1f));
}

void PageInfo::setSlot(int slot) { bitmap[slot >> 5] |= (1u << (slot & 0x1f)); }

void PageInfo::resetSlot(int slot) { bitmap[slot >> 5] &= ~(1u << (slot & 0x1f)); }
