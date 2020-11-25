#pragma once
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/MyHashMap.h"
#include "Record.hpp"
#include "FileHandler.hpp"
#include "utils.h"
#include "Types.hpp"
#include "BTree.hpp"
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

	bool create_index(const char* fileName, vector<int> indexNo, vector<AttrType> attrType, vector<int> attrLen) {
		int num = indexNo.size();
		if (attrType.size() != num) {
			return false;
		}
		if (attrLen.size() != num) {
			return false;
		}
		string newFile = string(fileName);
		for (int i = 0; i < num; ++i) {
			newFile = newFile + '_' + to_string(indexNo[i]);
		}
		// create file
		// TODO : ÐÞ¸ÄallLength
		int allLength = 4096 / 4;
		int fileID = create_file(newFile.c_str(), allLength);

		// set Index info and root
		FileHandler* fileHandler = new FileHandler(bpm, fileID);
		char* data;
		BTree* temp = new BTree(fileHandler);
		RecordID rID(0, 0);
		RecordID metaID(1, 0);
		TreeNode* root = new TreeNode();
		temp->setAttrs(attrType, attrLen);
		temp->setRoot(rID);

		// alloc metadata space and get metadata ID
		data = new char[4096];
		temp->getInfo(data);
		metaID = fileHandler->insertRecord((BufType)data);
		delete[] data;

		// alloc root node space and get root ID
		data = new char[4096];
		root->to_string(data);
		rID = fileHandler->insertRecord((BufType)data);
		delete[] data;
		delete root;

		// updata root to medatada
		data = new char[4096];
		temp->setRoot(rID);
		temp->getInfo(data);
		fileHandler->modifyRecord(metaID, (BufType)data);
		delete[] data;
		delete temp;
		return true;
	}

	bool delete_index(const char* fileName, vector<int> indexNo) {
		int num = indexNo.size();
		string newFile = string(fileName);
		for (int i = 0; i < num; ++i) {
			newFile = newFile + '_' + to_string(indexNo[i]);
		}
		// TODO : delete file
		return true;
	}

	bool open_index(const char* fileName, vector<int> indexNo, BTree **bTree) {
		int num = indexNo.size();
		string newFile = string(fileName);
		for (int i = 0; i < num; ++i) {
			newFile = newFile + '_' + to_string(indexNo[i]);
		}

		int fileID;
		fm->openFile(fileName, fileID);
		FileHandler* fileHandler = new FileHandler(bpm, fileID);

		// read No.1 record , set the bTree metadata
		RecordID index(1, 0);
		Record rec;
		fileHandler->getRecordById(index, rec);
		BTree* temp = new BTree(fileHandler);
		temp->setInfo(rec.getData());
		*bTree = temp;
		return true;
	}

	bool close_index(BTree* bTree) {
		delete bTree;
		return true;
	}
};
