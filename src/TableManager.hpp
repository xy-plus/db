#pragma once
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/MyHashMap.h"
#include "Record.hpp"
#include "FileHandler.hpp"
#include "utils.h"
#include "Table.hpp"
#include <vector>

using namespace std;

class IndexManager {
	FileManager* fm;
	BufPageManager* bpm;

	int create_file(const char* fileName, int recordLength) {
		fm->createFile(fileName);

		int fileID;
		fm->openFile(fileName, fileID);
		int index;

		MetadataPageInfo* metadata = (MetadataPageInfo*)bpm->allocPage(fileID, 0, index);
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

public:
	IndexManager(BufPageManager* bpm, FileManager* fm) {
		this->bpm = bpm;
		this->fm = fm;
	}

	bool create_index(const char* fileName, vector<Line> lines, vector<string> primaryKey) {
		// create file
		int allLength = 1024;
		int fileID = create_file(fileName, allLength);

		// set Index info and root
		FileHandler* fileHandler = new FileHandler(bpm, fileID);
		char* data;

		Table* temp = new Table(fileHandler);
		temp.setAttrs(lines);
		temp.setprimartKey(primaryKey);
		RecordID metaID(1, 0);
		
		// alloc metadata space and get metadata ID
		data = new char[4096];
		temp->getMetadata(data);
		metaID = fileHandler->insertRecord((BufType)data);
		delete[] data;

		delete temp;
		return true;
	}

	bool delete_index(const char* fileName) {
		// TODO : delete file
		return true;
	}

	bool open_index(const char* fileName, vector<int> indexNo, BTree** bTree) {
		int fileID;
		fm->openFile(fileName, fileID);
		FileHandler* fileHandler = new FileHandler(bpm, fileID);

		// read No.1 record , set the bTree metadata
		RecordID index(1, 0);
		Record rec;
		fileHandler->getRecordById(index, rec);
		Table* temp = new Table(fileHandler);
		temp->setMetadata(rec.getData());
		*bTree = temp;
		return true;
	}

	bool close_index(BTree* bTree) {
		delete bTree;
		return true;
	}
};
