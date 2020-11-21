#pragma once
#include <vector>
#include <string>
#include "utils.h"
#include "Types.hpp"

using namespace std;

class Value {
	vector<AttrType> attrs;
	vector<Type*> vals;
	friend class BTree;
public:
	Value() {
		attrs.clear();
		vals.clear();
	}

	~Value() {
		attrs.clear();
		for (int i = 0; i < vals.size(); ++i) {
			if (vals[i] != NULL) {
				delete vals[i];
			}
		}
		vals.clear();
	}

	int legnth() {
		/*
		1: int vals.size()
		n: int attrs
		n: int + length vals
		*/
		int len = sizeof(int) * (1 + vals.size() * 2);
		for (int i = 0; i < vals.size(); ++i) {
			len += vals[i]->getLength();
		}
		return len;
	}

	void setVals(char* data) {
		int offset = 0;
		int n = ((int*)(data + offset))[0];
		offset += sizeof(int);
		for (int i = 0; i < n; ++i) {
			int temp = ((int*)(data + offset))[0];
			attrs.push_back((AttrType)temp);
			offset += sizeof(int);
		}

		for (int i = 0; i < n; ++i) {
			int len = ((int*)(data + offset))[0];
			offset += sizeof(int);
			Type* tp;
			switch (attrs[i]) {
			case INTEGER:
				tp = new IntType();
				break;
			case DATE:
				tp = new DateType();
				break;
			case CHAR:
				tp = new CharType();
				break;
			case VARCHAR:
				tp = new VarcharType();
				break;
			case NUMERIC:
				tp = new NumericType();
				break;
			default:
				break;
			}
			tp->fromChars(data + offset, len);
			vals.push_back(tp);

			offset += len;
		}

	}

	void setVals(vector<Type*> val) {
		for (int i = 0; i < val.size(); ++i) {
			AttrType type = val[i]->getType();
			attrs.push_back(type);
			Type* temp;
			switch (type) {
			case INTEGER:
				temp = new IntType((IntType*)val[i]);
				break;
			case DATE:
				temp = new DateType((DateType*)val[i]);
				break;
			case CHAR:
				temp = new CharType((CharType*)val[i]);
				break;
			case VARCHAR:
				temp = new VarcharType((VarcharType*)val[i]);
				break;
			case NUMERIC:
				temp = new NumericType((NumericType*)val[i]);
				break;
			default:
				break;
			}
			vals.push_back(temp);
		}
	}

	string toString() {
		char* temp = new char[4096];
		int offset = 0;
		((int*)(temp + offset))[0] = vals.size();
		offset += sizeof(int);

		for (int i = 0; i < attrs.size(); ++i) {
			((int*)(temp + offset))[0] = attrs[i];
			offset += sizeof(int);
		}

		for (int i = 0; i < vals.size(); ++i) {
			int len;
			offset += sizeof(int);
			vals[i]->toChars(temp + offset, len);
			offset -= sizeof(int);
			((int*)(temp + offset))[0] = len;
			offset = offset + sizeof(int) + len;
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

		Type* temp1;
		Type* temp2;
		switch(ops[0]){
		case LE:
		case GE:
		case LT:
		case GT:
		case EQ:
			temp1 = this->vals[0];
			temp2 = b.vals[0];
			ok = temp1->cmp(temp2, ops[0]);
			break;
		default:
			// isnull、isnotnull、ne、in、no不能用于排序，默认符合
			break;
		}
		return ok;
	}

	bool check(Value b, vector<CmpOP> ops) {
		for (int i = 0; i < vals.size(); ++i) {
			if (!vals[i]->cmp(b.vals[i], ops[i])) {
				return false;
			}
		}
		return true;
	}
};