#pragma once
typedef unsigned int uint;

using namespace std;

struct RecordID {
    uint page, slot;

    RecordID(uint page_, uint slot_);
    RecordID();
	uint getPageID(int &pageID) const;
	uint getSlotID(int &slotID) const;
    void print();
    bool operator <(const RecordID &recordID) const;
    bool operator ==(const RecordID &recordID) const;
};

class Record {
   private:
    uint* data;
    RecordID rid;
    uint size;

   public:
    Record(uint* data_, uint size_, RecordID rid_);

    Record(const Record& a);

    Record(Record&& a);

    // 等价于 `=`
    void assign(const Record& a);

    Record();
    ~Record();

    uint* getData() const;
    RecordID getRecordID() const;
    uint getSize() const;
};
