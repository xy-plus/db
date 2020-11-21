#pragma once
#include <string>
#include <vector>
#include "utils.h"

using namespace std;

class Type {
	bool isNull = false;
public:

	virtual int getLength() {}

	void setIsNull(bool _null) {
		isNull = _null;
	}

	bool getIsNull() {
		return isNull;
	}

	virtual void toChars(char* buf, int& len) {}

	virtual void fromChars(char* buf, int len) {}

	virtual AttrType getType() {
		return INTEGER;
	}

	virtual bool isInt() {
		return false;
	}

	virtual bool isDate() {
		return false;
	}

	virtual bool isChar() {
		return false;
	}

	virtual bool isVarchar() {
		return false;
	}

	virtual bool isNumeric() {
		return false;
	}

	virtual bool cmp(Type* b, CmpOP op) {
		return false;
	}
};

// 整数类型
class IntType : public Type{
	int num;
public:
	IntType() {
		num = 0;
	}

	IntType(IntType* b) {
		num = b->num;
		this->setIsNull(b->getIsNull());
	}

	int getLength() {
		return 4;
	}

	void fromChars(char* buf, int len) {
		num = ((int*)(buf))[0];
	}

	bool isInt() {
		return true;
	}

	AttrType getType() {
		return INTEGER;
	}

	void setInt(int _num) {
		num = _num;
	}

	int getInt() {
		return num;
	}

	void toChars(char* buf, int& len) {
		len = 4;
		((int*)(buf))[0] = num;
	}

	bool cmp(Type* b, CmpOP op) {
		bool ok = false;
		if (b->isInt()) {
			IntType* temp = (IntType*)b;
			switch (op) {
				case EQ:
					if (b->getIsNull() || this->getIsNull())
						break;
					if (temp->num == num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case NE:
					if (b->getIsNull() || this->getIsNull())
						break;
					if (temp->num != num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case LT:
					if (b->getIsNull() || this->getIsNull())
						break;
					if (num < temp->num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case GT:
					if (b->getIsNull() || this->getIsNull())
						break;
					if (num > temp->num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case LE:
					if (b->getIsNull() || this->getIsNull())
						break;
					if (num <= temp->num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case GE:
					if (b->getIsNull() || this->getIsNull())
						break;
					if (num >= temp->num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case NO:
					ok = true;
					break;
				case ISNOTNULL:
					ok = !getIsNull();
					break;
				case ISNULL:
					ok = getIsNull();
					break;
				case IN:
					// TODO
					break;
				default:
					break;
			}
		} else {
			return false;
		}
		return ok;
	}
};

// 日期类型 yyyy-mm-dd
class DateType : public Type {
	int length;
	int year;
	int month;
	int day;

	bool setYear(int year) {
		if (year < 1000 || year > 9999) {
			return false;
		}
		this->year = year;
	}

	bool setMonth(int month) {
		if (month < 1 || month > 12) {
			return false;
		}
		this->month = month;
	}

	bool setDay(int day) {
		this->year = year;
	}

	bool equal(DateType* b) {
		if (b->year != year)
			return false;
		if (b->month != month)
			return false;
		if (b->day != day)
			return false;
		return true;
	}

	bool less(DateType* b) {
		if (b->year < year)
			return false;
		if (b->year > year)
			return true;

		if (b->month < month)
			return false;
		if (b->month > month)
			return true;

		if (b->day < day)
			return false;
		if (b->day > day)
			return true;
		return false;
	}
public:
	DateType() {
		year = 0;
		month = 0;
		day = 0;
	}

	DateType(DateType* b) {
		year = b->year;
		month = b->month;
		day = b->day;
		this->setIsNull(b->getIsNull());
	}

	int getLength() {
		return 10;
	}

	void fromChars(char* buf, int len) {
		int a, b, c, d;
		a = buf[0] - '0';
		b = buf[1] - '0';
		c = buf[2] - '0';
		d = buf[3] - '0';
		year = a * 1000 + b * 100 + c * 10 + d;

		a = buf[5] - '0';
		b = buf[6] - '0';
		month = a * 10 + b;

		a = buf[8] - '0';
		b = buf[9] - '0';
		day = a * 10 + b;
	}

	AttrType getType() {
		return DATE;
	}

	bool isDate() {
		return true;
	}

	void toChars(char* buf, int& len) {
		len = 10;
		int a, b, c, d;
		a = year / 1000;
		b = (year % 1000) / 100;
		c = (year % 100) / 10;
		d = year % 10;
		buf[0] = '0' + a;
		buf[1] = '0' + b;
		buf[2] = '0' + c;
		buf[3] = '0' + d;

		a = month / 10;
		b = month % 10;
		buf[4] = '-';
		buf[5] = '0' + a;
		buf[6] = '0' + b;

		a = day / 10;
		b = day % 10;
		buf[7] = '-';
		buf[8] = '0' + a;
		buf[9] = '0' + b;
	}

	int getYear() {
		return year;
	}

	int getMonth() {
		return month;
	}

	int getDay() {
		return day;
	}

	bool setDate(int y, int m, int d) {
		if (y < 1000 || y > 9999) {
			return false;
		}
		if (m < 1 || m > 12) {
			return false;
		}

		if (d < 1 || d > 31) {
			return false;
		}

		bool ok = false;
		if (y % 4 == 0) {
			if (y % 100 == 0) {
				if (y % 400 == 0) {
					ok = true;
				}	else {
					ok = false;
				}
			} else {
				ok = true;
			}
		}
		switch (m) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				ok = true;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				ok = true;
				if (d > 30) {
					ok = false;
				}
				break;
			case 2:
				if (ok) {
					ok = true;
					if (d > 29) {
						ok = false;
					}
				} else {
					ok = true;
					if (d > 28) {
						ok = false;
					}
				}
				break;
			default: ok = false;
		}

		if (ok == false) {
			return false;
		}

		this->year = y;
		this->month = m;
		this->day = d;
		return true;
	}

	bool cmp(Type* b, CmpOP op) {
		bool ok = false;
		if (b->isDate()) {
			DateType* temp = (DateType*)b;
			switch (op) {
			case EQ:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = equal(temp);
				break;
			case NE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = !equal(temp);
				break;
			case LT:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = less(temp);
				break;
			case GT:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = temp->less(this);
				break;
			case LE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = less(temp) | equal(temp);
				break;
			case GE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = temp->less(this) | equal(temp);
				break;
			case NO:
				ok = true;
				break;
			case ISNOTNULL:
				ok = !getIsNull();
				break;
			case ISNULL:
				ok = getIsNull();
				break;
			case IN:
				// TODO
				break;
			default:
				break;
			}
		}
		else {
			return false;
		}
		return ok;
	}
};

// 固定长度字符串
class CharType : public Type {
	int length;
	vector<char> val;

	bool equal(CharType* b) {
		if (b->length != this->length)
			return false;
		for (int i = 0; i < length; ++i)
			if (b->val[i] != this->val[i])
				return false;
		return true;
	}

	bool less(CharType* b) {
		string s1 = "";
		string s2 = "";
		for (int i = 0; i < length; ++i)
			s1 += this->val[i];
		for (int i = 0; i < b->length; ++i)
			s2 += b->val[i];
		return s1 < s2;
	}
public:
	CharType() {
		length = 0;
		val.clear();
	}

	CharType(CharType* b) {
		length = b->length;
		val.clear();
		for (int i = 0; i < b->val.size(); ++i) {
			val.push_back(b->val[i]);
		}
		this->setIsNull(b->getIsNull());
	}

	CharType(int len) {
		length = len;
		val.clear();
		for (int i = 0; i < len; ++i) {
			val.push_back(' ');
		}
	}

	~CharType() {
		val.clear();
	}

	int getLength() {
		return length;
	}

	void fromChars(char* buf, int len) {
		length = len;
		val.clear();
		for (int i = 0; i < len; ++i) {
			val.push_back(buf[i]);
		}
	}

	AttrType getType() {
		return CHAR;
	}

	bool isChar() {
		return true;
	}

	void setVal(string str) {
		if (str.length() <= length) {
			for (int i = 0; i < str.length(); ++i)
				val[i] = str[i];
			for (int i = str.length(); i < length; ++i)
				val[i] = ' ';
		} else {
			// error
		}
	}

	void toChars(char* buf, int& len) {
		len = length;
		for (int i = 0; i < length; ++i)
			buf[i] = val[i];
	}

	bool cmp(Type* b, CmpOP op) {
		bool ok = false;
		if (b->isChar()) {
			CharType* temp = (CharType*)b;
			switch (op) {
			case EQ:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = equal(temp);
				break;
			case NE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = !equal(temp);
				break;
			case LT:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = less(temp);
				break;
			case GT:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = temp->less(this);
				break;
			case LE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = less(temp) | equal(temp);
				break;
			case GE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = temp->less(this) | equal(temp);
				break;
			case NO:
				ok = true;
				break;
			case ISNOTNULL:
				ok = !getIsNull();
				break;
			case ISNULL:
				ok = getIsNull();
				break;
			case IN:
				// TODO
				break;
			default:
				break;
			}
		}
		else {
			return false;
		}
		return ok;
	}
};

// 变长字符串，有长度上限
class VarcharType : public Type {
	int maxlength;
	int length;
	vector<char> val;

	bool equal(VarcharType* b) {
		if (b->length != this->length)
			return false;
		for (int i = 0; i < length; ++i)
			if (b->val[i] != this->val[i])
				return false;
		return true;
	}

	bool less(VarcharType* b) {
		string s1 = "";
		string s2 = "";
		for (int i = 0; i < length; ++i)
			s1 += this->val[i];
		for (int i = 0; i < b->length; ++i)
			s2 += b->val[i];
		return s1 < s2;
	}
public:
	VarcharType() {
		maxlength = 0;
		length = 0;
		val.clear();
	}

	VarcharType(VarcharType* b) {
		maxlength = b->maxlength;
		length = b->length;
		val.clear();
		for (int i = 0; i < b->val.size(); ++i) {
			val.push_back(b->val[i]);
		}
		this->setIsNull(b->getIsNull());
	}

	VarcharType(int len) {
		maxlength = len;
		val.clear();
		for (int i = 0; i < len; ++i) {
			val.push_back(' ');
		}
	}

	~VarcharType() {
	}

	int getLength() {
		return maxlength;
	}

	void fromChars(char* buf, int len) {
		maxlength = len - 1;
		length = (int)(buf[0]);
		val.clear();
		for (int i = 0; i < length; ++i) {
			val.push_back(buf[i + 1]);
		}
	}

	AttrType getType() {
		return VARCHAR;
	}

	bool isVarchar() {
		return true;
	}

	void setVal(string str) {
		if (str.length() <= maxlength) {
			length = str.length();
			for (int i = 0; i < str.length(); ++i)
				val[i] = str[i];
		}
		else {
			// error
		}
	}

	void toChars(char* buf, int& len) {
		len = maxlength + 1;
		buf[0] = (char)length;
		for (int i = 0; i < length; ++i)
			buf[i + 1] = val[i];
	}

	bool cmp(Type* b, CmpOP op) {
		bool ok = false;
		if (b->isVarchar()) {
			VarcharType* temp = (VarcharType*)b;
			switch (op) {
			case EQ:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = equal(temp);
				break;
			case NE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = !equal(temp);
				break;
			case LT:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = less(temp);
				break;
			case GT:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = temp->less(this);
				break;
			case LE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = less(temp) | equal(temp);
				break;
			case GE:
				if (b->getIsNull() || this->getIsNull())
					break;
				ok = temp->less(this) | equal(temp);
				break;
			case NO:
				ok = true;
				break;
			case ISNOTNULL:
				ok = !getIsNull();
				break;
			case ISNULL:
				ok = getIsNull();
				break;
			case IN:
				// TODO
				break;
			default:
				break;
			}
		}
		else {
			return false;
		}
		return ok;
	}
};

// 小数，固定小数位数，总位数有限制
class NumericType : public Type {
	// TODO
	vector<int> num;
	int allLength;
	int backLength;


public:
	NumericType() {

	}

	NumericType(NumericType* b) {

	}

	AttrType getType() {
		return NUMERIC;
	}

	bool isNumeric() {
		return true;
	}
};