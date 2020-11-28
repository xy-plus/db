#pragma once
#include <string>
#include <vector>
#include "utils.h"

using namespace std;

class Type {
	bool isNull = false;
	AttrType type;

	/*
	num:
		int : num
		date : year month day
		char : length
		varchar : maxlength length
		numeric : allLength backLength;
	*/
	// num :
	vector<int> num;
	
	/*
	val: char¡¢varchar
	*/
	vector<char> val;
	
	/*
	TODO : numeric store
	*/

	// DATE
	bool setYear(int year) {
		if (year < 1000 || year > 9999) {
			return false;
		}
		num[0] = year;
	}

	bool setMonth(int month) {
		if (month < 1 || month > 12) {
			return false;
		}
		num[1] = month;
	}

	bool setDay(int day) {
		num[2] = day;
	}
	   	  
	bool equal(Type b) {
		if (this->getIsNull() != b.getIsNull())
			return false;
		if (this->getIsNull())
			return true;

		if (b.type != this->type)
			return false;
		switch (type) {
		case INTEGER:
			if (b.num[0] == this->num[0])
				return true;
			return false;
			break;
		case DATE:
			if (b.num[0] != this->num[0])
				return false;
			if (b.num[1] != this->num[1])
				return false;
			if (b.num[2] != this->num[2])
				return false;
			return true;
			break;
		case CHAR:
			if (b.num[0] != this->num[0])
				return false;
			for (int i = 0; i < this->num[0]; ++i)
				if (b.val[i] != this->val[i])
					return false;
			return true;
			break;
		case VARCHAR:
			if (b.num[1] != this->num[1])
				return false;
			for (int i = 0; i < this->num[1]; ++i)
				if (b.val[i] != this->val[i])
					return false;
			return true;
			break;
		case NUMERIC:
			// TODO
			break;
		default:
			break;
		}
		return false;
	}

	bool less(Type b) {
		if (b.getIsNull())
			return false;
		if (this->getIsNull())
			return true;

		if (b.type != this->type)
			return false;
		string s1 = "";
		string s2 = "";
		switch (type) {
		case INTEGER:
			if (this->num[0] < b.num[0])
				return true;
			return false;
			break;
		case DATE:
			if (this->num[0] < b.num[0])
				return true;
			if (this->num[0] > b.num[0])
				return false;

			if (this->num[1] < b.num[1])
				return true;
			if (this->num[1] > b.num[1])
				return false;

			if (this->num[2] < b.num[2])
				return true;
			if (this->num[2] > b.num[2])
				return false;
			return false;
			break;
		case CHAR:
			for (int i = 0; i < this->num[0]; ++i)
				s1 += this->val[i];
			for (int i = 0; i < b.num[0]; ++i)
				s2 += b.val[i];
			return s1 < s2;
			break;
		case VARCHAR:
			for (int i = 0; i < this->num[1]; ++i)
				s1 += this->val[i];
			for (int i = 0; i < b.num[1]; ++i)
				s2 += b.val[i];
			return s1 < s2;
			break;
		case NUMERIC:
			// TODO
			break;
		default:
			break;
		}
		return false;
	}
public:
	Type() {
		isNull = false;
		type = INTEGER;
		num.clear();
		val.clear();
	}

	void toChars(char* buf, int& len) {
		int tp = (int)type;
		buf[0] = (char)tp;

		if (isNull) tp = 1;
		else tp = 0;
		buf[1] = (char)tp;

		buf = buf + 2;
		len = 2;
		int a, b, c, d;
		switch (type) {
		case INTEGER:
			len += 4;
			((int*)buf)[0] = num[0];
			break;
		case DATE:
			len += 12;
			((int*)buf)[0] = num[0];
			((int*)buf)[1] = num[1];
			((int*)buf)[2] = num[2];
			break;
		case CHAR:
			len += num[0];
			for (int i = 0; i < num[0]; ++i)
				buf[i] = val[i];
			break;
		case VARCHAR:
			len += num[0] + 1;
			buf[0] = (char)num[1];
			for (int i = 0; i < num[1]; ++i)
				buf[i + 1] = val[i];
			break;
		case NUMERIC:
			// TODO
			break;
		default:
			break;
		}
	}

	void fromChars(char* buf, int len) {
		int tp = (int)(buf[0]);
		type = (AttrType)tp;
		tp = (int)(buf[1]);
		if (tp == 0) isNull = false;
		  else isNull = true;

		buf = buf + 2;

		setAttrType(type);
		switch (type) {
		case INTEGER:
			num[0] = ((int*)(buf))[0];
			break;
		case DATE:
			num[0] = ((int*)(buf))[0];
			num[1] = ((int*)(buf))[1];
			num[2] = ((int*)(buf))[2];
			break;
		case CHAR:
			num[0] = len - 2;
			val.clear();
			for (int i = 0; i < num[0]; ++i) {
				val.push_back(buf[i]);
			}
			break;
		case VARCHAR:
			num[0] = len - 3;
			num[1] = (int)(buf[0]);
			val.clear();
			for (int i = 0; i < num[1]; ++i) {
				val.push_back(buf[i + 1]);
			}
			for (int i = num[1]; i < num[0]; ++i) {
				val.push_back(' ');
			}
			break;
		case NUMERIC:
			// TODO
			break;
		default:
			break;
		}
	}

	void setValue(Type b) {
		isNull = b.isNull;
		setAttrType(b.type);
		switch (b.type) {
		case INTEGER:
			num[0] = b.num[0];
			break;
		case DATE:
			num[0] = b.num[0];
			num[1] = b.num[1];
			num[2] = b.num[2];
			break;
		case CHAR:
			num[0] = b.num[0];
			val.clear();
			for (int i = 0; i < b.val.size(); ++i) {
				val.push_back(b.val[i]);
			}
			break;
		case VARCHAR:
			num[0] = b.num[0];
			num[1] = b.num[1];
			val.clear();
			for (int i = 0; i < b.val.size(); ++i) {
				val.push_back(b.val[i]);
			}
			break;
		case NUMERIC:
			// TODO
			break;
		default:
			break;
		}
	}

	// INTEGER
	void setInt(int _num) {
		num[0] = _num;
	}

	int getInt() {
		return num[0];
	}

	// DATE
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
				}
				else {
					ok = false;
				}
			}
			else {
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
			}
			else {
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

		num[0] = y;
		num[1] = m;
		num[2] = d;
		return true;
	}

	int getYear() {
		return num[0];
	}

	int getMonth() {
		return num[1];
	}

	int getDay() {
		return num[2];
	}

	// CHAR & VARCHAR
	void setVal(string str) {
		if (str.length() <= num[0]) {
			for (int i = 0; i < str.length(); ++i)
				val[i] = str[i];

			if (type == CHAR) {
				for (int i = str.length(); i < num[0]; ++i)
					val[i] = ' ';
			}
			else if (type == VARCHAR) {
				num[1] = str.length();
			}
		}
		else {
			// error
		}
	}

	void setLen(int len) {
		num[0] = len;
		for (int i = 0; i < len; ++i) {
			val.push_back(' ');
		}
	}

	int getLen() {
		return num[0];
	}

	// TODO : NUMERIC

	void setAttrType(AttrType tp) {
		type = tp;
		num.clear();
		val.clear();
		switch (type) {
		case INTEGER:
			num.push_back(0);
			break;
		case DATE:
			num.push_back(0);
			num.push_back(0);
			num.push_back(0);
			break;
		case CHAR:
			num.push_back(0);
			break;
		case VARCHAR:
			num.push_back(0);
			num.push_back(0);
			break;
		case NUMERIC:
			// TODO
			break;
		default:
			break;
		}
	}

	int getLength() {
		// 1 £º type ¡¢ varchar's num[1]
		switch (type) {
		case INTEGER:
			return 4 + 2;
			break;
		case DATE:
			return 12 + 2;
			break;
		case CHAR:
			return num[0] + 2;
			break;
		case VARCHAR:
			return num[0] + 1 + 2;
			break;
		case NUMERIC:
			// TODO
			break;
		default:
			break;
		}
		return 0;
	}

	void setIsNull(bool _null) {
		isNull = _null;
	}

	bool getIsNull() {
		return isNull;
	}

	AttrType getType() {
		return type;
	}

	bool isInt() {
		if (type == INTEGER) {
			return true;
		}
		return false;
	}

	bool isDate() {
		if (type == DATE) {
			return true;
		}
		return false;
	}

	bool isChar() {
		if (type == CHAR) {
			return true;
		}
		return false;
	}

	bool isVarchar() {
		if (type == VARCHAR) {
			return true;
		}
		return false;
	}

	bool isNumeric() {
		if (type == NUMERIC) {
			return true;
		}
		return false;
	}

	bool cmp(Type b, CmpOP op, bool checked) {
		bool ok = false;
		if (b.type == this->type) {
			switch (op) {
			case EQ:
				if ((checked) && (b.getIsNull() || this->getIsNull()))
					break;
				ok = equal(b);
				break;
			case NE:
				if ((checked) && (b.getIsNull() || this->getIsNull()))
					break;
				ok = !equal(b);
				break;
			case LT:
				if ((checked) && (b.getIsNull() || this->getIsNull()))
					break;
				ok = less(b);
				break;
			case GT:
				if ((checked) && (b.getIsNull() || this->getIsNull()))
					break;
				ok = !(less(b) | equal(b));
				break;
			case LE:
				if ((checked) && (b.getIsNull() || this->getIsNull()))
					break;
				ok = less(b) | equal(b);
				break;
			case GE:
				if ((checked) && (b.getIsNull() || this->getIsNull()))
					break;
				ok = !less(b);
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
