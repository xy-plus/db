#pragma once
#include "Record.hpp"
#include "FileHandler.hpp"
#include "utils.h"
#include "Types.hpp"
#include "Value.hpp"
#include "TreeNode.hpp"
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/MyHashMap.h"
#include <vector>
#include <string>
#define MAX_RECORD_SIZE 4096

using namespace std;

class BTree {
	// TODO : uodata record
public:
	BTree(FileHandler* fileHandler) {
		this->fileHandler = fileHandler;
	}

	bool update_Record(RecordID rid, RecordID newrid, vector<Type> oldVal, vector<Type> newVal) {
		Value oldKey;
		Value newKey;
		oldKey.setVals(oldVal);
		newKey.setVals(newVal);
		if (checkType(newKey) == false) {
			return false;
		}
		if (searchNode(root, oldKey, rid)) {
			if (!searchNode(root, newKey, newrid)) {
				deleteNode(root, oldKey, rid);
				insertNode(root, newrid, newKey);
			} else {
				// has the same key and rid
				return false;
			}
		} else {
			// no old Record
			return false;
		}
		return true;
	}

	bool insert_Record(RecordID rid, vector<Type> vals) {
		// new Record
		Value newKey;
		newKey.setVals(vals);
		RecordID oldID;
		if (checkType(newKey) == false) {
			return false;
		}
		if (!searchNode(root, newKey, rid)) {
			insertNode(root, rid, newKey);
		} else {
			// has the same key and rid
			return false;
		}
		return true;
	}

	bool delete_Record(vector<Type> vals, RecordID rid) {
		Value oldKey;
		oldKey.setVals(vals);
		return deleteNode(root, oldKey, rid);
	}

	vector<RecordID> find_Record(vector<Type> vals, vector<CmpOP> ops) {
		Value key;
		key.setVals(vals);
		return findNode(root, key, ops);
	}


private:
	friend class IndexManager;
	RecordID root;
	int num;

	int numAttr;
	vector<Types> attrTypes;
	vector<int> attrLen;

	FileHandler* fileHandler;

	bool compare(Value a, Value b, CmpOP op) {
		int len = a.size();
		if (b.size() != len) {
			return false;
		} else {
			for (int i = 0; i < len; ++i) {
				Type a0 = a.getVal(i);
				Type b0 = b.getVal(i);
				if (!a0.cmp(b0, op, false)) {
					return false;
				}
			}
		}
		return true;
	}

	bool checkType(Value a) {
		// TODO Numeric
		if (a.size() != numAttr) {
			return false;
		}
		for (int i = 0; i < numAttr; ++i) {
			Type temp = a.getVal(i);
			if (temp.getType() != attrTypes[i])
				return false;
			if (attrTypes[i] == T_CHAR | attrTypes[i] == VARCHAR) {
				if (attrLen[i] != temp.getLen()) {
					return false;
				}
			}
		}
		return true;
	}

	void setAttrs(vector<Types> types, vector<int> lens) {
		num = 0;
		numAttr = types.size();
		attrTypes.assign(types.begin(), types.end());
		attrLen.assign(lens.begin(), lens.end());
	}

	void setRoot(RecordID rt) {
		root = rt;
	}

	void getInfo(char* data) {
		getMetaData((uint*)data);
	}

	void setInfo(uint* data) {
		setMetadata(data);
	}

	void setMetadata(uint* data) {
		num = (int)data[0];
		root.page = (int)data[1];
		root.slot = (int)data[2];
		numAttr = (int)data[3];
		for (int i = 0; i < numAttr; ++i) {
			int a = (int)data[4 + i * 2];
			int b = (int)data[5 + i * 2];
			attrTypes.push_back((Types)a);
			attrLen.push_back(b);
		}
	}

	void getMetaData(uint* data) {
		data[0] = (uint)num;
		data[1] = (uint)root.page;
		data[2] = (uint)root.slot;
		data[3] = (uint)numAttr;
		for (int i = 0; i < numAttr; ++i) {
			data[4 + i * 2] = (uint)attrTypes[i];
			data[5 + i * 2] = (uint)attrLen[i];
		}
	}

	TreeNode* getNode(RecordID rid) {
		Record temp;
		TreeNode* p;
		if (fileHandler->getRecordById(rid, temp)) {
			p = new TreeNode((char*)temp.getData());
		}
		else {
			p = new TreeNode();
		}
		return p;
	}

	void saveNode(RecordID rid, TreeNode* temp) {
		char* buffer = new char[4096];
		temp->to_string(buffer);
		fileHandler->modifyRecord(rid, (BufType)buffer);
		delete[] buffer;
	}

	RecordID newNode() {
		char* buffer = new char[4096];
		TreeNode* temp = new TreeNode();
		temp->to_string(buffer);
		RecordID metaID = fileHandler->insertRecord((BufType)buffer);
		delete temp;
		delete[] buffer;
		return metaID;
	}

	bool getPrevNode(RecordID now, RecordID& prev) {
		TreeNode* temp = getNode(now);
		RecordID fID = temp->getFather();
		if (fID.page != 0) {
			TreeNode* father = getNode(fID);
			int k = father->findChild(now);
			if (k > 0) {
				prev = father->getChild(k - 1);
				return true;
			} else {
				return false;
			}
			delete father;
		} else {
			return false;
		}
		delete temp;
	}

	bool getSuccNode(RecordID now, RecordID& succ) {
		TreeNode* temp = getNode(now);
		RecordID fID = temp->getFather();
		if (fID.page != 0) {
			TreeNode* father = getNode(fID);
			int k = father->findChild(now);
			if (k < father->getKeyNum() - 1) {
				succ = father->getChild(k + 1);
				return true;
			} else {
				return false;
			}
			delete father;
		} else {
			return false;
		}
		delete temp;
	}

	vector<RecordID> findNode(RecordID now, Value key, vector<CmpOP> ops) {
		TreeNode* temp = getNode(now);
		vector<RecordID> ans;
		ans.clear();
		if (temp->isLeaf) {
			int keyNum = temp->getKeyNum();
			for (int i = 0; i < keyNum; ++i) {
				Value val = temp->getKey(i);
				if (val.check(key, ops)) {
					ans.push_back(temp->getChild(i));
				}
			}
		} else {
			int keyNum = temp->getKeyNum();
			int addr = keyNum - 1;
			bool last = true;
			bool next = false;
			for (int i = 0; i < keyNum; ++i) {
				Value val = temp->getKey(i);
				last = next;
				next = val.cmp(key, ops);
				if (last | next) {
					vector<RecordID> tempAns = findNode(temp->getChild(i), key, ops);
					for (int j = 0; j < tempAns.size(); ++j) {
						ans.push_back(tempAns[j]);
					}
				}
			}
		}
		delete temp;
		return ans;
	}

	bool searchNode(RecordID now, Value key, RecordID rID) {
		TreeNode* temp = getNode(now);
		if (temp->isLeaf) {
			int keyNum = temp->getKeyNum();
			for (int i = 0; i < keyNum; ++i) {
				if (compare(key, temp->getKey(i), T_EQ)) {
					RecordID tempID = temp->getChild(i);
					if (equalRID(rID, tempID))
						return true;
				}
			}
		}
		else {
			int keyNum = temp->getKeyNum();
			int addr = keyNum - 1;
			for (int i = 0; i < keyNum; ++i) {
				if (compare(key, temp->getKey(i), T_LE)) {
					addr = i;
					break;
				}
			}
			bool answer = searchNode(temp->getChild(addr), key, rID);

			if (answer) {
				return true;
			}
		}
		delete temp;
		return false;
	}

	bool insertNode(RecordID now, RecordID recordID, Value newValue) {
		TreeNode* temp = getNode(now);
		if (temp->isLeaf) {
			int keyNum = temp->getKeyNum();
			int addr = keyNum;
			for (int i = 0; i < keyNum; ++i) {
				if (compare(newValue, temp->getKey(i), T_LE)) {
					addr = i;
					break;
				}
			}
			temp->insertKey(addr, newValue);
			temp->insertChild(addr, recordID);
			saveNode(now, temp);
		}
		else {
			int keyNum = temp->getKeyNum();
			int addr = keyNum - 1;
			for (int i = 0; i < keyNum; ++i) {
				if (compare(newValue, temp->getKey(i), T_LE)) {
					addr = i;
					break;
				}
			}
			bool answer = insertNode(temp->getChild(addr), recordID, newValue);
			if (answer == false) {
				delete temp;
				return false;
			}
		}
		delete temp;

		// 更新father的key
		temp = getNode(now);
		RecordID fID = temp->getFather();
		if (fID.page != 0) {
			TreeNode* father = getNode(fID);
			int k = father->findChild(now);
			father->modifyKey(k, temp->getKey(temp->getKeyNum() - 1));
			saveNode(fID, father);
			delete father;
		}
		if (temp->getKeyNum() > BTreeM) {
			if (fID.page == 0) {
				// split root
				RecordID lID = newNode();
				RecordID rID = newNode();

				TreeNode* newLeft = getNode(lID);
				TreeNode* newRight = getNode(rID);
				for (int i = 0; i < temp->getKeyNum(); ++i) {
					RecordID cID = temp->getChild(i);
					if (temp->isLeaf) {
						if (i < LIMIT) {
							newLeft->insertKey(i, temp->getKey(i));
							newLeft->insertChild(i, cID);
						}
						else {
							newRight->insertKey(i - LIMIT, temp->getKey(i));
							newRight->insertChild(i - LIMIT, cID);
						}
					}
					else {
						TreeNode* temp_c = getNode(cID);
						if (i < LIMIT) {
							newLeft->insertKey(i, temp->getKey(i));
							newLeft->insertChild(i, cID);
							temp_c->setFather(lID);
							saveNode(cID, temp_c);
						}
						else {
							newRight->insertKey(i - LIMIT, temp->getKey(i));
							newRight->insertChild(i - LIMIT, cID);
							temp_c->setFather(rID);
							saveNode(cID, temp_c);
						}
						delete temp_c;
					}
				}
				int k1 = LIMIT - 1;
				int k2 = temp->getKeyNum() - LIMIT - 1;

				newLeft->setFather(now);
				newRight->setFather(now);
				newLeft->setIsLeaf(temp->isLeaf);
				newRight->setIsLeaf(temp->isLeaf);
				temp->isLeaf = false;
				temp->clear();
				temp->insertChild(0, lID);
				temp->insertChild(1, rID);
				temp->insertKey(0, newLeft->getKey(k1));
				temp->insertKey(1, newRight->getKey(k2));
				saveNode(now, temp);
				saveNode(lID, newLeft);
				saveNode(rID, newRight);

				delete newLeft;
				delete newRight;
			} else {
				RecordID bro;
				TreeNode* temp_bro;
				bool ok = false;
				if (getPrevNode(now, bro)) {
					temp_bro = getNode(bro);
					if (temp_bro->getKeyNum() < BTreeM) {
						ok = true;
						// move front to left back
						RecordID tID;
						Value tKey;
						temp->pop_front(tID, tKey);
						
						if (!temp->isLeaf) {
							TreeNode* temp_c = getNode(tID);
							temp_c->setFather(bro);
							saveNode(tID, temp_c);
							delete temp_c;
						}

						int k = temp_bro->getKeyNum();
						temp_bro->insertChild(k, tID);
						temp_bro->insertKey(k, tKey);

						TreeNode* father = getNode(fID);
						k = father->findChild(bro);
						father->modifyKey(k, tKey);

						saveNode(fID, father);
						saveNode(now, temp);
						saveNode(bro, temp_bro);

						delete father;
					}
					delete temp_bro;
				}
				if (ok == false) {
					if (getSuccNode(now, bro)) {
						temp_bro = getNode(bro);
						if (temp_bro->getKeyNum() < BTreeM) {
							ok = true;
							// move back to right front
							RecordID tID;
							Value tKey;
							temp->pop_back(tID, tKey);

							if (!temp->isLeaf) {
								TreeNode* temp_c = getNode(tID);
								temp_c->setFather(bro);
								saveNode(tID, temp_c);
								delete temp_c;
							}

							temp_bro->insertChild(0, tID);
							temp_bro->insertKey(0, tKey);

							TreeNode* father = getNode(fID);
							int k = father->findChild(now);
							father->modifyKey(k, temp->getKey(temp->getKeyNum() - 1));

							saveNode(fID, father);
							saveNode(now, temp);
							saveNode(bro, temp_bro);

							delete father;
						}
						delete temp_bro;
					}
				}
				if (ok == false) {
					// split and add to father
					RecordID lID = newNode();
					TreeNode* newLeft = getNode(lID);

					for (int i = 0; i < LIMIT; ++i) {
						RecordID cID = temp->getChild(i);

						if (!temp->isLeaf) {
							TreeNode* temp_c = getNode(cID);
							temp_c->setFather(lID);
							saveNode(cID, temp_c);
							delete temp_c;
						}
						newLeft->insertKey(i, temp->getKey(i));
						newLeft->insertChild(i, cID);
					}
					for (int i = 0; i < LIMIT; ++i) {
						newLeft->deleteKey(0);
						newLeft->deleteChild(0);
					}

					TreeNode* father = getNode(fID);

					newLeft->setFather(fID);
					newLeft->setIsLeaf(temp->isLeaf);

					int k = father->findChild(now);
					if (k > -1) {
						father->insertChild(k, lID);
						father->insertKey(k, newLeft->getKey(LIMIT - 1));
						saveNode(now, temp);
						saveNode(lID, newLeft);
						saveNode(fID, father);
					}

					delete father;
					delete newLeft;
				}
			}
		}
		delete temp;
		return true;
	}

	bool deleteNode(RecordID now, Value newValue, RecordID orid) {
		TreeNode* temp = getNode(now);
		if (temp->isLeaf) {
			int keyNum = temp->getKeyNum();
			int addr = -1;
			for (int i = 0; i < keyNum; ++i) {
				if (compare(newValue, temp->getKey(i), T_EQ)) {
					RecordID rid0 = temp->getChild(i);
					if (rid0.page == orid.page && rid0.slot == orid.slot) {
						addr = i;
						break;
					}
				}
			}
			if (addr == -1) {
				delete temp;
				return false;
			}
			temp->deleteKey(addr);
			temp->deleteChild(addr);
			saveNode(now, temp);
		}
		else {
			int keyNum = temp->getKeyNum();
			int addr = -1;
			for (int i = 0; i < keyNum; ++i) {
				if (compare(newValue, temp->getKey(i), T_LE)) {
					addr = i;
					break;
				}
			}
			if (addr == -1) {
				delete temp;
				return false;
			}
			bool answer = deleteNode(temp->getChild(addr), newValue, orid);

			if (answer == false) {
				delete temp;
				return false;
			}
		}
		delete temp;
		// 更新father的key
		temp = getNode(now);
		RecordID fID = temp->getFather();
		if (fID.page != 0 && temp->getKeyNum() > 0) {
			TreeNode* father = getNode(fID);
			int k = father->findChild(now);
			father->modifyKey(k, temp->getKey(temp->getKeyNum() - 1));
			saveNode(fID, father);
			delete father;
		}
		if (temp->getKeyNum() < LIMIT) {
			if (fID.page == 0) {
				// 一般不处理，只有root child为空时重设为leaf
				if (temp->getKeyNum() == 0) {
					temp->isLeaf = true;
					saveNode(now, temp);
				}
			}
			else {
				if (temp->getKeyNum() == 0) {
					// keys number = 0,need to delete from father
					TreeNode* father = getNode(fID);
					int k = father->findChild(now);
					father->deleteChild(k);
					father->deleteKey(k);
					saveNode(fID, father);

					delete father;
				}
			}
		}
		delete temp;
		return true;
	}
};
