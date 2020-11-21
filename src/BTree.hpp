#pragma once
#include "Record.hpp"
#include "FileHandler.hpp"
#include "utils.h"
#include "Types.hpp"
#include "TreeNode.hpp"
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/MyHashMap.h"
#include <vector>
#include <string>
#define MAX_RECORD_SIZE 4096

using namespace std;

class BTree {
	// TODO : uodata record & vector<Type*>
public:
	BTree(BufPageManager* bpm, FileManager* fm) {
		this.bpm = bpm;
		this.fm = fm;
	}

	~BTree() {
	}

	bool update_Record(RecordID rid, RecordID newrid, vector<Type*> oldVal, vector<Type*> newVal) {
		Value oldKey;
		Value newKey;
		oldKey.setVals(oldVal);
		newKey.setVals(newVal);
		RecordID oldID;
		if (searchNode(root, oldKey, oldID)) {
			if (oldID == rid) {
				if (!searchNode(root, newKey, oldID)) {
					deleteNode(root, oldKey);
					insertNode(root, rid, newKey);
				} else {
					// has the same new key
					return false;
				}
			} else {
				// old ID error
				return false;
			}
		} else {
			// no old Record
			return false;
		}
		return true;
	}

	bool insert_Record(RecordID rid, vector<Type*> vals) {
		// new Record
		Value newKey;
		newKey.setVals(vals);
		RecordID oldID;
		if (!searchNode(root, newKey, oldID)) {
			insertNode(root, rid, newKey);
		} else {
			// has the same key
			return false;
		}
		return true;
	}

	bool delete_Record(vector<Type*> vals) {
		Value oldKey;
		oldKey.setVals(vals);
		return deleteNode(root, oldKey);
	}

	vector<RecordID> find_Record(vector<Type*> vals, vector<CmpOP> ops) {
		Value key;
		key.setVals(vals);
		return findNode(root, key, ops);
	}

	bool rebuild() {
		// TODO
	}

private:
	friend class IndexHandler;
	RecordID root;
	int num;

	int numAttr;
	vector<AttrType> attrTypes;
	vector<int> attrLen;

	FileManager* fm;
	BufPageManager* bpm;
	FileHandler* fileHandler;

	bool compare(Value a, Value b, CmpOP op) {
		int len = a.legnth();
		if (b.legnth() != len) {
			return false;
		} else {
			for (int i = 0; i < len; ++i) {
				Type a0 = a.getVal(i);
				Type b0 = b.getVal(i);
				if (!a0.cmp(b0, op)) {
					return false;
				}
			}
		}
		return true;
	}

	void setAttrs(vector<AttrType> types, vector<int> lens) {
		num = 0;
		numAttr = types.size();
		attrTypes.assign(types.begin(), types.end());
		attrLen.assign(lens.begin(), lens.end());
	}

	void setRoot(RecordID rt) {
		root = rt;
	}

	void getInfo(char* data) {
		data = new char[4096];
		int size;
		getMetaData((uint*)data, size);
	}

	void setInfo(uint* data, int size) {
		setMetadata(data, size);
	}

	void setMetadata(uint* data, int size) {
		num = (int)data[0];
		int page = (int)data[1];
		int slot = (int)data[2];
		root = new RecordID(page, slot);
		numAttr = (int)data[3];
		for (int i = 0; i < numAttr; ++i) {
			int a, b;
			a = (AttrType)data[4 + i * 2];
			b = (int)data[5 + i * 2];
			attrTypes.push_back(a);
			attrLen.push_back(b);
		}
	}

	void getMetaData(uint* data, int& size) {
		data = new uint[4096];
		data[0] = (uint)num;
		data[1] = (uint)root.page;
		data[2] = (uint)root.slot;
		data[2] = (uint)numAttr;
		for (int i = 0; i < numAttr; ++i) {
			data[4 + i * 2] = (uint)attrTypes[i];
			data[5 + i * 2] = (uint)attrLen[i];
		}
		size = 4096;
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
		BufType record;
		temp->to_string((char*)record);
		fileHandler->modifyRecord(rid, record);
	}

	bool getPrevNode(RecordID now, RecordID& prev) {
		TreeNode* temp = getNode(now);
		RecordID fID = temp->getFather();
		if (fID.page != -1) {
			TreeNode* father = getNode(fID);
			int k = father->findChild(now);
			if (k > 0) {
				prev = father->getChild(k - 1);
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	bool getSuccNode(RecordID now, RecordID& succ) {
		TreeNode* temp = getNode(now);
		RecordID fID = temp->getFather();
		if (fID.page != -1) {
			TreeNode* father = getNode(fID);
			int k = father->findChild(now);
			if (k < father->getKeyNum() - 1) {
				succ = father->getChild(k + 1);
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}

	vector<RecordID> findNode(RecordID now, Value key, Vector<CmpOP> ops) {
		TreeNode* temp = getNode(now);
		vector<RecordID> ans;
		ans.clear();
		if (temp.isLeaf) {
			int keyNum = temp.getKeyNum();
			for (int i = 0; i < keyNum; ++i) {
				Value val = temp->getKey(i);
				if (val.check(key, ops) == 0) {
					ans.push_back(temp->getChild(i));
				}
			}
		} else {
			int keyNum = temp.getKeyNum();
			int addr = keyNum - 1;
			for (int i = 0; i < keyNum; ++i) {
				// TODO
				Value val = temp->getKey(i);
				if (val.cmp(key, ops) >= 1) {
					vector<RecordID> tempAns = findNode(temp->getChild(i), key, ops);
					for (int j = 0; j < tempAns.size(); ++j) {
						ans.push_back(tempAns[j]);
					}
				}
			}
		}
		return ans;
	}

	bool searchNode(RecordID now, Value key, RecordID &rID) {
		TreeNode* temp = getNode(now);
		if (temp.isLeaf) {
			int keyNum = temp.getKeyNum();
			for (int i = 0; i < keyNum; ++i) {
				if (compare(key, temp->getKey(i), EQ)) {
					rID = temp.getChild(i);
					return true;
				}
			}
		}
		else {
			int keyNum = temp.getKeyNum();
			int addr = keyNum - 1;
			for (int i = 0; i < keyNum; ++i) {
				if (compare(key, temp->getKey(i), LE)) {
					addr = i;
					break;
				}
			}
			bool answer = searchNode(temp->getChild(addr), key, rID);

			if (answer) {
				return true;
			}
		}
		return false;
	}

	bool insertNode(RecordID now, RecordID recordID, Value newValue) {
		TreeNode* temp = getNode(now);
		if (temp->isLeaf) {
			int keyNum = temp->getKeyNum();
			int addr = keyNum;
			for (int i = 0; i < keyNum; ++i) {
				if (compare(newValue, temp->getKey(i), LE)) {
					addr = i;
					break;
				}
			}
			temp->insertKey(addr, newValue);
			temp->insertChild(addr, recordID);
			save(now, temp);
		}
		else {
			int keyNum = temp->getKeyNum();
			int addr = keyNum - 1;
			for (int i = 0; i < keyNum; ++i) {
				if (compare(newValue, temp->getKey(i), LE)) {
					addr = i;
					break;
				}
			}
			bool answer = insertNode(temp->getChild(addr), recordID, newValue);

			if (answer == false) {
				return false;
			}
		}
		// 更新father的key
		temp = getNode(now);
		RecordID fID = temp.getFather();
		if (fID.page != -1) {
			TreeNode* father = getNode(fID);
			int k = father->findChild(now);
			father->modifyKey(k, temp->getKey(temp->getKeyNum() - 1));
			saveNode(fID, father);
		}
		if (temp->getKeyNum() > BTreeM) {
			if (fID.page == -1) {
				// split root
				RecordID lID = newNode();
				RecordID rID = newNode();
				TreeNode* newLeft = getNode(lID);
				TreeNode* newRight = getNode(rID);
				for (int i = 0; i < temp->getKeyNum(); ++i) {
					RecordID cID = temp->getChild(i);
					TreeNode* temp_c = getNode(cID);
					if (i < LIMIT) {
						newLeft->insertKey(i, temp->getKey(i));
						newLeft->insertChild(i, cID);
						temp_c->setFather(lID);
						saveNode(cID, temp_c);
					} else {
						newRight->insertKey(i - LIMIT, temp->getKey(i));
						newRight->insertChild(i - LIMIT, cID);
						temp_c->setFather(rID);
						saveNode(cID, temp_c);
					}
				}
				int k1 = LIMIT - 1;
				int k2 = temp->getKeyNum - LIMIT;

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
						TreeNode* temp_c = getNode(tID);
						temp_c->setFather(bro);

						int k = temp_bro->getKeyNum();
						temp_bro->insertChild(k, tID);
						temp_bro->insertKey(k, tKey);

						TreeNode* father = getNode(fID);
						int k = father->findChild(bro);
						father->modifyKey(k, tKey);

						saveNode(fID, father);
						saveNode(now, temp);
						saveNode(bro, temp_bro);
						saveNode(tID, temp_c);
					}
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
							TreeNode* temp_c = getNode(tID);
							temp_c->setFather(bro);

							temp_bro->insertChild(0, tID);
							temp_bro->insertKey(0, tKey);

							TreeNode* father = getNode(fID);
							int k = father->findChild(now);
							father->modifyKey(k, temp->getKey(temp->getKeyNum()));

							saveNode(fID, father);
							saveNode(now, temp);
							saveNode(bro, temp_bro);
							saveNode(tID, temp_c);
						}
					}
				}
				if (ok == false) {
					// split and add to father
					RecordID lID = newNode();
					TreeNode* newLeft = getNode(lID);

					for (int i = 0; i < Limit; ++i) {
						RecordID cID = temp->getChild(i);
						TreeNode* temp_c = getNode(cID);
						newLeft->insertKey(i, temp->getKey(i));
						newLeft->insertChild(i, cID);
						temp_c->setFather(lID);
						saveNode(cID, temp_c);
					}
					for (int i = 0; i < Limit; ++i) {
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
				}
			}
		}
		return true;
	}

	bool deleteNode(RecordID now, Value newValue) {
		TreeNode* temp = getNode(now);
		if (temp->isLeaf) {
			int keyNum = temp.getKeyNum();
			int addr = -1;
			for (int i = 0; i < keyNum; ++i) {
				if (cmp(newValue, temp->getKey(i), EQ)) {
					addr = i;
					break;
				}
			}
			if (addr == -1) {
				return false;
			}
			temp->deleteKey(addr);
			temp->deleteChild(addr);
			save(now, temp);
		}
		else {
			int keyNum = temp.getKeyNum();
			int addr = -1;
			for (int i = 0; i < keyNum; ++i) {
				if (cmp(newValue, temp->getKey(i), LE)) {
					addr = i;
					break;
				}
			}
			if (addr == -1) {
				return false;
			}
			bool answer = insertNode(temp->getChild(addr), recordID, newValue);

			if (answer == false) {
				return false;
			}
		}
		// 更新father的key
		temp = getNode(now);
		RecordID fID = temp.getFather();
		if (fID.page != -1 && temp->getKeyNum() > 0) {
			TreeNode* father = getNode(fID);
			int k = father->findChild(now);
			father->modifyKey(k, temp->getKey(temp->getKeyNum() - 1));
			saveNode(fID, father);
		}
		if (temp->getKeyNum() < LIMIT) {
			if (fID.page == -1) {
				// 一般不处理，只有root child为空时重设为leaf
				if (temp->getKeyNum() == 0) {
					temp->isLeaf = true;
					saveNode(now, temp);
				}
			}
			else {
				RecordID bro;
				TreeNode* temp_bro;
				// TODO : only empty will delete
				bool ok = false;
				if (getPrevNode(now, bro)) {
					temp_bro = getNode(bro);
					if (temp_bro->getKeyNum() > LIMIT) {
						ok = true;
						// move left back to front
						RecordID tID;
						Value tKey;
						temp_bro->pop_back(tID, tKey);
						TreeNode* temp_c = getNode(tID);
						temp_c->setFather(now);

						temp->insertChild(0, tID);
						temp->insertKey(0, tKey);

						TreeNode* father = getNode(fID);
						int k = father->findChild(bro);
						father->modifyKey(k, temp_bro->getKey(temp_bro->getKeyNum()));

						saveNode(fID, father);
						saveNode(now, temp);
						saveNode(bro, temp_bro);
						saveNode(tID, temp_c);
					}
				}
				if (ok == false) {
					if (getSuccNode(now, bro)) {
						temp_bro = getNode(bro);
						if (temp_bro->getKeyNum() > LIMIT) {
							ok = true;
							// move right fornt to back
							RecordID tID;
							Value tKey;
							temp_bro->pop_front(tID, tKey);
							TreeNode* temp_c = getNode(tID);
							temp_c->setFather(now);

							int k = temp->getKeyNum();
							temp->insertChild(k, tID);
							temp->insertKey(k, tKey);

							TreeNode* father = getNode(fID);
							k = father->findChild(now);
							father->modifyKey(k, tKey);

							saveNode(fID, father);
							saveNode(now, temp);
							saveNode(bro, temp_bro);
							saveNode(tID, temp_c);
						}
					}
				}
				if (ok == false) {
					if (getPrevNode(now, bro)) {
						// combine bro to now
						temp_bro = getNode(bro);
						for (int i = 0; i < temp_bro->getKeyNum(); ++i) {
							RecordID cID = temp_bro->getChild(i);
							TreeNode* temp_c = getNode(cID);
							temp->insertKey(0, temp_bro->getKey(i));
							temp->insertChild(0, cID);
							temp_c->setFather(now);
							saveNode(cID, temp_c);
						}

						TreeNode* father = getNode(fID);
						int k = father->findChild(bro);
						father->deleteChild(k);
						father->deleteKey(k);
						saveNode(fID, father);
						saveNode(now, temp);
					} else if (getSuccNode(now, bro)) {
						// combine now to bro
						temp_bro = getNode(bro);
						for (int i = 0; i < temp->getKeyNum(); ++i) {
							RecordID cID = temp->getChild(i);
							TreeNode* temp_c = getNode(cID);

							temp_bro->insertKey(0, temp->getKey(i));
							temp_bro->insertChild(0, cID);

							temp_c->setFather(bro);
							saveNode(cID, temp_c);
						}

						TreeNode* father = getNode(fID);
						int k = father->findChild(now);
						father->deleteChild(k);
						father->deleteKey(k);
						saveNode(fID, father);
						saveNode(bro, temp_bro);
					}
					else if (temp->getKeyNum() == 0) {
						// keys number = 0,need to delete from father
						TreeNode* father = getNode(fID);
						int k = father->findChild(now);
						father->deleteChild(k);
						father->deleteKey(k);
						saveNode(fID, father);
					}
				}
			}
		}
		return true;
	}
};
