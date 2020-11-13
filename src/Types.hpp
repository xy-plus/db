#pragma once
#include <string>
#include <vector>
#include "utils.h"

using namespace std;

class Type {
	bool isNull;
public:
	void setIsNull(bool _null) {
		isNull = _null;
	}
	void toChars(char* buf, int& len) {};

	AttrType getType() {
		return 0;
	}

	bool getIsNull() {
		return isNull;
	}

	bool isInt() {
		return false;
	}

	bool isDate() {
		return false;
	}

	bool isChar() {
		return false;
	}

	bool isVarChar() {
		return false;
	}

	bool isNumeric() {
		return false;
	}

	bool cmp(Type b, CmpOP op) {
		return false;
	}
};

// 整数类型
class IntType : public Type{
	int num;
public:
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
		buf = new char[4];
		len = 4;
		((int*)(buf))[0] = num;
	}

	bool cmp(Type b, CmpOP op) {
		bool ok = false;
		if (b.isInt()) {
			IntType temp = (IntType)b;
			switch (op) {
				case EQ:
					if (b.getIsNull() || this->getIsNull())
						break;
					if (temp.num == num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case NE:
					if (b.getIsNull() || this->getIsNull())
						break;
					if (temp.num != num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case LT:
					if (b.getIsNull() || this->getIsNull())
						break;
					if (num < temp.num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case GT:
					if (b.getIsNull() || this->getIsNull())
						break;
					if (num > temp.num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case LE:
					if (b.getIsNull() || this->getIsNull())
						break;
					if (num <= temp.num) {
						ok = true;
					} else {
						ok = false;
					}
					break;
				case GE:
					if (b.getIsNull() || this->getIsNull())
						break;
					if (num >= temp.num) {
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
				case ISNOTNULL:
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
		if (yaer < 1000 || year > 9999) {
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

	bool equal(DateType b) {
		if (b.year != year)
			return false;
		if (b.month != month)
			return false;
		if (b.day != day)
			return false;
	}

	bool less(DateType b) {
		if (b.year < year)
			return false;
		if (b.year > year)
			return true;

		if (b.month < month)
			return false;
		if (b.month > month)
			return true;

		if (b.day < day)
			return false;
		if (b.day > day)
			return true;
		return false;
	}
public:
	DateType() {
		year = 0;
		month = 0;
		day = 0;
	}

	DateType(DateType a) {
		year = a.year;
		month = a.month;
		day = a.day;
	}

	AttrType getType() {
		return DATE;
	}

	bool isDate() {
		return true;
	}

	void toChars(char* buf, int& len) {
		len = 10;
		buf = new char[10];
		int a, b, c, d;
		a = year / 1000;
		b = (yaer % 1000) / 100;
		c = (yaer % 100) / 10;
		d = yaer % 10;
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

	bool cmp(Type b, CmpOP op) {
		bool ok = false;
		if (b.isDate()) {
			DateType temp = (DateType)b;
			switch (op) {
			case EQ:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = equal(temp);
				break;
			case NE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = !equal(temp);
				break;
			case LT:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = less(temp);
				break;
			case GT:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = temp.less(*this);
				break;
			case LE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = less(temp) | equal(temp);
				break;
			case GE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = temp.less(*this) | equal(temp);
				break;
			case NO:
				ok = true;
				break;
			case ISNOTNULL:
				ok = !getIsNull();
				break;
			case ISNOTNULL:
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

	bool equal(CharType b) {
		if (b.length != this->length)
			return false;
		for (int i = 0; i < length; ++i)
			if (b.val[i] != this->val[i])
				return false;
	}

	bool less(CharType b) {
		string s1 = "";
		string s2 = "";
		for (int i = 0; i < length; ++i)
			s1 += this.val[i];
		for (int i = 0; i < b.length; ++i)
			s2 += b.val[i];
		return s1 < s2;
	}
public:
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
		buf = new char[length + 1];
		buf[0] = (char)len;
		for (int i = 0; i < length; ++i)
			buf[i + 1] = val[i];
	}

	bool cmp(Type b, CmpOP op) {
		bool ok = false;
		if (b.isChar()) {
			CharType temp = (CharType)b;
			switch (op) {
			case EQ:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = equal(temp);
				break;
			case NE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = !equal(temp);
				break;
			case LT:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = less(temp);
				break;
			case GT:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = temp.less(*this);
				break;
			case LE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = less(temp) | equal(temp);
				break;
			case GE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = temp.less(*this) | equal(temp);
				break;
			case NO:
				ok = true;
				break;
			case ISNOTNULL:
				ok = !getIsNull();
				break;
			case ISNOTNULL:
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

	bool equal(VarcharType b) {
		if (b.length != this->length)
			return false;
		for (int i = 0; i < length; ++i)
			if (b.val[i] != this->val[i])
				return false;
	}

	bool less(VarcharType b) {
		string s1 = "";
		string s2 = "";
		for (int i = 0; i < length; ++i)
			s1 += this.val[i];
		for (int i = 0; i < b.length; ++i)
			s2 += b.val[i];
		return s1 < s2;
	}
public:
	VarcharType(int len) {
		maxlength = len;
		val.clear();
		for (int i = 0; i < len; ++i) {
			val.push_back(' ');
		}
	}

	~VarcharType() {
	}

	AttrType getType() {
		return VARCHAR;
	}

	bool isVarChar() {
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
		len = length;
		buf = new char[length + 1];
		buf[0] = (char)len;
		for (int i = 0; i < length; ++i)
			buf[i + 1] = val[i];
	}

	bool cmp(Type b, CmpOP op) {
		bool ok = false;
		if (b.isVarchar()) {
			VarcharType temp = (VarcharType)b;
			switch (op) {
			case EQ:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = equal(temp);
				break;
			case NE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = !equal(temp);
				break;
			case LT:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = less(temp);
				break;
			case GT:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = temp.less(*this);
				break;
			case LE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = less(temp) | equal(temp);
				break;
			case GE:
				if (b.getIsNull() || this->getIsNull())
					break;
				ok = temp.less(*this) | equal(temp);
				break;
			case NO:
				ok = true;
				break;
			case ISNOTNULL:
				ok = !getIsNull();
				break;
			case ISNOTNULL:
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
	Vector<int> num;
	int allLength;
	int backLength;


public:
	AttrType getType() {
		return NUMERIC;
	}

	bool isNumeric() {
		return true;
	}
};