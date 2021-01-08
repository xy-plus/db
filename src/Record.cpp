#include <iostream>
#include <string.h>
#include "Record.h"

using namespace std;

RecordID::RecordID(uint page_, uint slot_) : page(page_), slot(slot_) {}
RecordID::RecordID() : RecordID(0, 0) {}
uint RecordID::getPageID(int &pageID) const { pageID = page; }
uint RecordID::getSlotID(int &slotID) const { slotID = slot; }
void RecordID::print() { cout << "page: " << page << ", slot: " << slot << endl; }
bool RecordID::operator <(const RecordID &recordID) const {
    return this->page < recordID.page || (this->page== recordID.page && this->slot < recordID.slot);
}
bool RecordID::operator ==(const RecordID &recordID) const {
    return this->page == recordID.page && this->slot == recordID.slot;
}

Record::Record(uint* data_, uint size_, RecordID rid_) : size(size_), rid(rid_) {
    data = new uint[size];
    memcpy(data, data_, size * sizeof(uint));
}

Record::Record(const Record& a) {
    cout << "TODO: 拷贝构造函数..." << endl;
    exit(-1);
    // rid = a.getRecordID();
    // size = a.getSize();
    // data = new uint[size];
    // memcpy(data, a.getData(), size * sizeof(uint));
}

Record::Record(Record&& a) {
    cout << "TODO: 移动构造函数..." << endl;
    exit(-1);
    // rid = a.getRecordID();
    // data = new uint[size];
    // memcpy(data, a.getData(), a.getSize() * sizeof(uint));
}

// 等价于 `=`
void Record::assign(const Record& a) {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    rid = a.getRecordID();
    size = a.getSize();
    data = new uint[size];
    memcpy(data, a.getData(), size * sizeof(uint));
}

Record::Record(): data(nullptr), size(0) {}

Record::~Record() {
    if (data != nullptr)
        delete[] data;
}

uint* Record::getData() const { return data; }
RecordID Record::getRecordID() const { return rid; }
uint Record::getSize() const { return size; }
