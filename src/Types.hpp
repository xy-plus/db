#pragma once
#include <string>
#include "utils.h"

using namespace std;

class Type {
public:
	void toChars(char* buf, int& len) {};

	AttrType getType() {
		return 0;
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
	// TODO
public:
	bool isInt() {
		return true;
	}

	AttrType getType() {
		return INTEGER;
	}

	bool cmp(Type b, CmpOP op) {
		// TODO
		bool ok = false;
		if (b.isInt()) {
			switch (op) {
				case EQ:
					break;
				case NE:
					break;
				case LT:
					break;
				case GT:
					break;
				case LE:
					break;
				case GE:
					break;
				case NO:
					break;
				case ISNOTNULL:
					break;
				case ISNOTNULL:
					break;
				case IN:
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
};

// 固定长度字符串
class CharType : public Type {
	int length;
	char* val;
public:
	CharType(int len) {
		length = len;
		val = new char[len];
	}

	~CharType() {
		delete[] val;
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
		buf = new char[length];
		for (int i = 0; i < length; ++i)
			buf[i] = val[i];
	}
};

// 变长字符串，有长度上限
class VarcharType : public Type {
	int maxlength;
	int length;
	char* val;
public:
	VarcharType(int len) {
		maxlength = len;
		val = new char[len];
	}

	~VarcharType() {
		delete[] val;
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
		buf = new char[length];
		for (int i = 0; i < length; ++i)
			buf[i] = val[i];
	}
};

// 小数，固定小数位数，总位数有限制
class NumericType : public Type {
	// TODO
public:
	AttrType getType() {
		return NUMERIC;
	}

	bool isNumeric() {
		return true;
	}
};