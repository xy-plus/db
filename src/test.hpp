#ifndef TEST_HPP
#define TEST_HPP

#include <cstring>
#include <string>
#include "FileHandler.hpp"
#include "Record.hpp"

bool check(Record& r) {
    return r.getData()[0] == 7;
}

string myFmt(string s, int len) {
    string ret;
    int a = (len - s.length()) / 2;
    for (int i = 0; i < a; ++i)
        ret += '-';
    ret += ' ' + s + ' ';
    for (int i = 0; i < a; ++i)
        ret += '-';
    return ret;
}

void test_select(FileHandler* fh) {
    cout << "test select begin" << endl;
    Record records[100];
    int count = fh->selectRecord(records, check);
    cout << "count: " << count << endl;
    for (int i = 0; i < count; ++i) {
        records[i].getRecordID().print();
    }
    cout << "test select end" << endl;
}

void test_insert(FileHandler* fh, uint record_len) {
    cout << "test insert begin" << endl;
    uint data[2048];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < record_len; ++j)
            data[j] = i + j;
        fh->insertRecord(data);
    }
    cout << "test insert end" << endl;
}

void test_modify(FileHandler* fh, uint record_len) {
    cout << "test modify begin" << endl;
    uint data[2048];
    for (int j = 0; j < record_len; ++j)
        data[j] = 7;
    assert(fh->modifyRecord(RecordID(1, 2), data));
    assert(fh->modifyRecord(RecordID(1, 3), data));
    assert(!fh->modifyRecord(RecordID(1, 6), data));
    cout << "test modify end" << endl;
}

void test_delete(FileHandler* fh, uint record_len) {
    cout << "test delete begin" << endl;
    assert(fh->deleteRecord(RecordID(1, 1)));
    assert(!fh->deleteRecord(RecordID(1, 6)));
    uint data[2048];
    for (int j = 0; j < record_len; ++j)
        data[j] = 7;
    fh->insertRecord(data);
    fh->insertRecord(data);
    cout << "test delete end" << endl;
}

void test_db(FileHandler* fh, uint record_len) {
    assert(record_len == 300);  // 以上测试数据都是在 300 的情况下设置的
    cout << myFmt("test db begin", 30) << endl;
    // cout << "--------------------------------" << endl;
    test_insert(fh, record_len);
    test_modify(fh, record_len);
    test_delete(fh, record_len);
    test_select(fh);
    cout << myFmt("test db end", 30) << endl;
}

#endif
