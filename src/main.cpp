#include <iostream>
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/MyHashMap.h"
#include "FileHandler.hpp"
#include "Record.hpp"
#include "test.hpp"
using namespace std;

const char testFileName[] = "test.txt";

FileManager* fm;
BufPageManager* bpm;

void init() {
    MyBitMap::initConst();
    fm = new FileManager();
    bpm = new BufPageManager(fm);
}

FileHandler* openFile(const char* filename) {
    int fileID;
    assert(fm->openFile(filename, fileID));
    return new FileHandler(bpm, fileID);
}

int createFile(const char* filename, unsigned recordLength) {
    fm->createFile(filename);
    int fileID;
    fm->openFile(filename, fileID);
    int index;
    MetadataPageInfo* metadata =
        (MetadataPageInfo*)bpm->allocPage(fileID, 0, index);
    bpm->markDirty(index);
    metadata->pageCount = 2;
    metadata->recordLength = recordLength;
    metadata->recordCount = 0;
    metadata->nextAvailPage = 1;
    metadata->pageSlotNumber = PAGE_SLOT_COUNT / recordLength;

    BufType secondPage = bpm->allocPage(fileID, 1, index);
    PageInfo* pg = (PageInfo*)secondPage;
    bpm->markDirty(index);
    pg->pageNumber = 1;
    pg->nextAvailPage = 0;
    fm->closeFile(fileID);

    return fileID;
}

void exit_db() {
    bpm->close();
    delete fm;
}

int main() {
    init();
    int record_len = 300;
    createFile(testFileName, record_len);
    FileHandler* fh = openFile(testFileName);
    test_db(fh, record_len);
    exit_db();
    return 0;
}
