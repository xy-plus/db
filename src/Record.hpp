#include "../filesystem/utils/pagedef.h"

#ifndef RECORD_HPP
#define RECORD_HPP
#include <iostream>

using namespace std;

struct RecordID {
    uint page, slot;

    RecordID(uint page_, uint slot_) : page(page_), slot(slot_) {}
    RecordID() : RecordID(0, 0) {}
	uint getPageID(int &pageID) const { pageID = page; }
	uint getSlotID(int &slotID) const { slotID = slot; }
    void print() { cout << "page: " << page << ", slot: " << slot << endl; }
};

class Record {
   private:
    uint* data;
    RecordID rid;
    uint size;

   public:
    Record(uint* data_, uint size_, RecordID rid_) : size(size_), rid(rid_) {
        data = new uint[size];
        memcpy(data, data_, size * sizeof(uint));
    }

    Record(const Record& a) {
        cout << "TODO: 拷贝构造函数..." << endl;
        exit(-1);
        // rid = a.getRecordID();
        // size = a.getSize();
        // data = new uint[size];
        // memcpy(data, a.getData(), size * sizeof(uint));
    }

    Record(Record&& a) {
        cout << "TODO: 移动构造函数..." << endl;
        exit(-1);
        // rid = a.getRecordID();
        // data = new uint[size];
        // memcpy(data, a.getData(), a.getSize() * sizeof(uint));
    }

    // 等价于 `=`
    void assign(const Record& a) {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
        rid = a.getRecordID();
        size = a.getSize();
        data = new uint[size];
        memcpy(data, a.getData(), size * sizeof(uint));
    }

    Record() : data(nullptr), size(0) {}
    ~Record() {
        if (data != nullptr)
            delete[] data;
    }

    uint* getData() const { return data; }
    RecordID getRecordID() const { return rid; }
    uint getSize() const { return size; }
};

#endif
