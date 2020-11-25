#pragma once
#include <vector>
#include <string>
#include "utils.h"
#include "Types.hpp"

using namespace std;

class Value {
	vector<Type> vals;
	friend class BTree;
public:
	Value() {
		vals.clear();
	}
	
	~Value() {
		vals.clear();
	}

	int length() {
		/*
		1: int vals.size()
		n: int + length vals
		*/
		int len = sizeof(int);
		for (int i = 0; i < vals.size(); ++i) {
			len += vals[i].getLength() + sizeof(int);
		}
		return len;
	}

	int size() {
		return vals.size();
	}

	Type getVal(int i) {
		return vals[i];
	}

	void setVals(char* data) {
		int offset = 0;
		int n = ((int*)(data + offset))[0];
		offset += sizeof(int);
		
		for (int i = 0; i < n; ++i) {
			int len = ((int*)(data + offset))[0];
			offset += sizeof(int);
			Type tp;
			tp.fromChars(data + offset, len);
			vals.push_back(tp);
			offset += len;
		}

	}

	void setVals(vector<Type> val) {
		vals.clear();
		for (int i = 0; i < val.size(); ++i) {
			vals.push_back(val[i]);
		}
	}

	void setVals(Value b) {
		vals.clear();
		for (int i = 0; i < b.vals.size(); ++i) {
			vals.push_back(b.vals[i]);
		}
	}

	string toString() {
		char* temp = new char[4096];
		int offset = 0;
		((int*)(temp + offset))[0] = vals.size();
		offset += sizeof(int);
		
		for (int i = 0; i < vals.size(); ++i) {
			int len;
			offset += sizeof(int);
			vals[i].toChars(temp + offset, len);
			offset -= sizeof(int);
			((int*)(temp + offset))[0] = len;
			offset += sizeof(int) + len;
		}
		string s = "";
		for (int i = 0; i < offset; ++i) {
			s = s + temp[i];
		}

		delete[] temp;
		return s;
	}

	bool cmp(Value b, vector<CmpOP> ops) {
		// 用于find，只考虑第一个val
		bool ok = true;
		switch(ops[0]){
		case LE:
		case GE:
		case LT:
		case GT:
			ok = this->vals[0].cmp(b.vals[0], ops[0]);
			break;
		case EQ:
			ok = this->vals[0].cmp(b.vals[0], GE);
			break;
		default:
			// isnull、isnotnull、ne、in、no不能用于排序，默认符合
			break;
		}
		return ok;
	}

	bool check(Value b, vector<CmpOP> ops) {
		for (int i = 0; i < vals.size(); ++i) {
			if (!vals[i].cmp(b.vals[i], ops[i])) {
				return false;
			}
		}
		return true;
	}
};