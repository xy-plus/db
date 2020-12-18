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
	val: char、varchar
	*/
	vector<char> val;
	
	/*
	numeric : numeric 从低到高存储，高低位补0
	opt: 正负
	*/
	vector<int> numeric;
	bool opt;

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
	   	
	// Numeric
	vector<int> getFront(int l) {
		vector<int> temp;
		temp.clear();
		// 从低位开始存储
		for (int i = num[1]; i < num[0]; ++i)
			temp.push_back(numeric[i]);
		for (int i = num[0] - num[1]; i < l; ++i)
			temp.push_back(0);
		return temp;
	}

	vector<int> getBack(int l) {
		vector<int> temp;
		temp.clear();
		// 从高位开始存储
		for (int i = num[1] - 1; i >= 0; --i)
			temp.push_back(numeric[i]);
		for (int i = num[1]; i < l; ++i)
			temp.push_back(0);
		return temp;
	}

	bool equal(Type b) {
		if (this->getIsNull() != b.getIsNull())
			return false;
		if (this->getIsNull())
			return true;

		if (b.type != this->type)
			return false;
		vector<int> t1;
		vector<int> t2;
		int l1, l2;
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
			if (b.opt != this->opt)
				return false;

			l1 = num[0] - num[1];
			l2 = b.num[0] - b.num[1];
			if (l1 < l2) l1 = l2;
			t1 = getFront(l1);
			t2 = b.getFront(l1);
			for (int i = 0; i < l1; ++i)
				if (t1[i] != t2[i])
					return false;

			l1 = num[1];
			l2 = b.num[1];
			if (l1 < l2) l1 = l2;
			t1 = getBack(l1);
			t2 = b.getBack(l1);
			for (int i = 0; i < l1; ++i) {
				if (t1[i] != t2[i])
					return false;
			}
			return true;
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
		vector<int> t1;
		vector<int> t2;
		int l1, l2;
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
			if (b.opt == true && this->opt == false)
				return true;
			if (b.opt == false && this->opt == true)
				return true;
			if (this->opt == true) {
				l1 = num[0] - num[1];
				l2 = b.num[0] - b.num[1];
				if (l1 < l2) l1 = l2;
				t1 = getFront(l1);
				t2 = b.getFront(l1);
				// 整数部分 从大到小 比较
				for (int i = l1 - 1; i >= 0; --i) {
					if (t1[i] < t2[i])
						return true;
					if (t1[i] > t2[i])
						return false;
				}

				l1 = num[1];
				l2 = b.num[1];
				if (l1 < l2) l1 = l2;
				t1 = getBack(l1);
				t2 = b.getBack(l1);
				// 小数部分 从小到大 比较
				for (int i = 0; i < l1; ++i) {
					if (t1[i] < t2[i])
						return true;
					if (t1[i] > t2[i])
						return false;
				}
				return false;
			}
			else {
				// 负数 大小相反
				l1 = num[0] - num[1];
				l2 = b.num[0] - b.num[1];
				if (l1 < l2) l1 = l2;
				t1 = getFront(l1);
				t2 = b.getFront(l1);
				// 整数部分 从大到小 比较
				for (int i = l1 - 1; i >= 0; --i) {
					if (t1[i] < t2[i])
						return false;
					if (t1[i] > t2[i])
						return true;
				}

				l1 = num[1];
				l2 = b.num[1];
				if (l1 < l2) l1 = l2;
				t1 = getBack(l1);
				t2 = b.getBack(l1);
				// 小数部分 从小到大 比较
				for (int i = 0; i < l1; ++i) {
					if (t1[i] < t2[i])
						return false;
					if (t1[i] > t2[i])
						return true;
				}
				return false;
			}
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
			len += num[0] + 3;
			buf[0] = (char)num[0];
			buf[1] = (char)num[1];
			if (opt) buf[2] = (char)1;
				else buf[2] = (char)0;
			for (int i = 0; i < num[0]; ++i)
				buf[i + 3] = (char)numeric[i];
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
			num[0] = (int)(buf[0]);
			num[1] = (int)(buf[1]);
			tp = (int)(buf[2]);
			if (tp == 0) opt = true;
			  else opt = false;
			for (int i = 0; i < num[0]; ++i)
				numeric.push_back((int)buf[3 + i]);
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
			num[0] = b.num[0];
			num[1] = b.num[1];
			opt = b.opt;
			numeric.clear();
			for (int i = 0; i < num[0]; ++i)
				numeric.push_back(b.numeric[i]);
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

	// TODO : more way set get NUMERIC
	void setNumericLength(int allLen = 20, int backLen = 2) {
		num[0] = allLen;
		num[1] = backLen;
		numeric.clear();
		for (int i = 0; i < allLen; ++i) {
			numeric.push_back(0);
		}
	}

	int getNumericAllLength() {
		return num[0];
	}

	int getNumericBackLength() {
		return num[1];
	}

	double getNumeric() {
		vector<int> t1 = getFront(num[0] - num[1]);
		double temp = 0;
		double a = 1;
		for (int i = 0; i < num[0] - num[1]; ++i) {
			temp = temp + a * t1[i];
			a = a * 10;
		}
		t1 = getBack(num[1]);
		a = 0.1;
		for (int i = 0; i <  num[1]; ++i) {
			temp = temp + a * t1[i];
			a = a / 10;
		}
		return temp;
	}

	void setNumeric(double nums) {
		if (nums < 0) {
			nums = -nums;
			setNumericOpt(false);
		}
		long long temp = trunc(nums);
		double d = nums - temp;
		if (num[1] == 0) {
			temp = round(nums);
		}
		for (int i = num[1]; i < num[0]; ++i) {
			numeric[i] = temp % 10;
			temp = temp / 10;
		}
		for (int i = 0; i < num[1]; ++i) {
			d = d * 10;
			numeric[i] = trunc(d);
			if (i == num[1] - 1) {
				numeric[i] = round(d);
			}
		}
	}

	string getNumericString() {
		string temp = "";
		if (opt == false) temp = "-";
		int l = num[0] - 1;
		while (l >= 0 && numeric[l] != 0) {
			l--;
		}
		for (int i = l; i >= num[1]; --i)
			temp = temp + to_string(numeric[i]);
		if (num[1] > 0)
			temp = temp + ".";
		for (int i = num[1] - 1; i >= 0; --i)
			temp = temp + to_string(numeric[i]);
		return temp;
	}

	void setNumericString(string nums) {
		int l = 0;
		if (nums[0] == '-') {
			l = 1;
			setNumericOpt(false);
		}
		int len = nums.length();
		vector<int> t1;
		t1.clear();
		while (l < len) {
			char ch = nums[l];
			if (ch == '.') {
				l++;
				break;
			}
			t1.push_back(ch - '0');
			l++;
		}
		for (int i = 0; i < t1.size(); ++i) {
			numeric[num[1] + t1.size() - 1 - i] = t1[i];
		}
		t1.clear();
		while (l < len) {
			char ch = nums[l];
			t1.push_back(ch - '0');
			l++;
		}
		for (int i = 0; i < t1.size(); ++i) {
			if (nums[1] <= i)
				break;
			numeric[nums[1] - 1 - i] = t1[i];
		}
	}

	void setNumericOpt(bool _opt) {
		opt = _opt;
	}

	bool getNumericOpt() {
		return opt;
	}

	void setAttrType(AttrType tp) {
		type = tp;
		num.clear();
		val.clear();
		numeric.clear();
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
			num.push_back(0);
			num.push_back(0);
			opt = true;
			break;
		default:
			break;
		}
	}

	int getLength() {
		// 1 ： type 、 isnull、
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
			// varchar's num[1]
			return num[0] + 1 + 2;
			break;
		case NUMERIC:
			// all、back、opt
			return 3 + num[0] + 2;
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
