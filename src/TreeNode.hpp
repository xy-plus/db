#pragma once
#include <vector>
#include <string>
#include "utils.h"
#include "Types.hpp"
#include "Record.hpp"
#include "FileHandler.hpp"
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/MyHashMap.h"
#define MAX_RECORD_SIZE 4096

using namespace std;

int BTreeM = 5;
int LIMIT = (BTreeM % 2) ? (BTreeM + 1) / 2 : BTreeM / 2;

bool equalRID(RecordID a, RecordID b) {
	if ((a.page != b.page) || (a.slot != b.slot))
		return false;
	return true;
}

class TreeNode {
public:
	TreeNode() {
		key.clear();
		child.clear();
		father.page = 0;
		father.slot = 0;
		isLeaf = true;
	}

	TreeNode(char* data) {
		from_chars(data);
	}

	void from_chars(char* data) {
		key.clear();
		child.clear();

		int keySize = ((int*)(data + offsetM))[0];
		int num = ((int*)(data + offsetIsLeaf))[0];
		if (num == 0) {
			isLeaf = false;
		}
		else {
			isLeaf = true;
		}

		father = ((RecordID*)(data + offsetFather))[0];

		RecordID * rbuf = (RecordID*)(data + offsetChild);
		for (int i = 0; i < keySize; ++i)
			child.push_back(rbuf[i]);

		int offset = offsetChild + keySize * sizeof(RecordID);
		int attrLength = ((int*)(data + offset))[0];
		offset = offset + sizeof(int);

		char* cbuf = (char*)(data + offset);
		char* temp = new char[attrLength];
		for (int i = 0; i < keySize; ++i) {
			memcpy(temp, cbuf, (size_t)attrLength);
			cbuf += attrLength;
			Value temp_v;
			temp_v.setVals(temp);
			key.push_back(temp_v);
		}
		delete[] temp;
	}

	void to_string(char* data) {
		((int*)(data + offsetM))[0] = key.size();
		((int*)(data + offsetIsLeaf))[0] = (int)isLeaf;
		((RecordID*)(data + offsetFather))[0] = father;

		RecordID * rbuf = (RecordID*)(data + offsetChild);
		for (int i = 0; i < child.size(); ++i)
			rbuf[i] = child[i];

		int attrLength = 0;
		if (key.size() > 0) {
			attrLength = key[0].length();
		}
		int offset = offsetChild + child.size() * sizeof(RecordID);
		((int*)(data + offset))[0] = attrLength;
		offset = offset + sizeof(int);

		int sumLen = offset;

		char* cbuf = (char*)(data + offset);
		for (int i = 0; i < key.size(); ++i) {
			memcpy(cbuf, key[i].toString().c_str(), (size_t)attrLength);
			cbuf += attrLength;
			sumLen += attrLength;
		}
	}

	int getKeyNum() {
		return key.size();
	}

	Value getKey(int num) {
		if (num < 0 || num >= key.size()) {
			// error
		}
		return key[num];
	}

	RecordID getChild(int num) {
		if (num < 0 || num >= child.size()) {
			// error
		}
		return child[num];
	}

	void insertKey(int num, Value data) {
		if (num > key.size()) {
			// error
			return;
		}
		if (num == key.size()) {
			key.push_back(data);
		}
		else {
			key.insert(key.begin() + num, data);
		}
	}

	void insertChild(int num, RecordID data) {
		if (num > child.size()) {
			// error
			return;
		}
		if (num == child.size()) {
			child.push_back(data);
		}
		else {
			child.insert(child.begin() + num, data);
		}
	}

	void modifyKey(int num, Value data) {
		if (num > key.size()) {
			// error
			return;
		}
		key[num] = data;
	}

	RecordID getFather() {
		return father;
	}

	void setFather(RecordID father) {
		this->father = father;
	}

	bool getIsLeaf() {
		return this->isLeaf;
	}

	void setIsLeaf(bool isLeaf) {
		this->isLeaf = isLeaf;
	}

	void clear() {
		key.clear();
		child.clear();
	}

	void pop_back(RecordID & rID, Value & k) {
		rID = child.back();
		k = key.back();
		child.pop_back();
		key.pop_back();
	}

	void pop_front(RecordID & rID, Value & k) {
		rID = child.front();
		k = key.front();
		child.erase(child.begin());
		key.erase(key.begin());
	}

	void deleteKey(int i) {
		key.erase(key.begin() + i);
	}

	void deleteChild(int i) {
		child.erase(child.begin() + i);
	}

	int findChild(RecordID cID) {
		for (int i = 0; i < child.size(); ++i) {
			if (equalRID(child[i], cID)) {
				return i;
			}
		}
		return -1;
	}
private:
	//RecordID index;
	vector<Value> key;
	vector<RecordID> child;
	RecordID father;
	bool isLeaf;

	static const int offsetM = 0;
	static const int offsetIsLeaf = sizeof(int) + offsetM;
	static const int offsetFather = sizeof(int) + offsetIsLeaf;
	static const int offsetChild = sizeof(RecordID) + offsetFather;

	friend class BTree;
};