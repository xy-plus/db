#ifndef DATABASE_PRINTER_H
#define DATABASE_PRINTER_H

#include <iomanip>
#include "global.h"
#include "parser/Tree.h"
#include "RecordDescriptor.h"

template <class T>
int length(T obj) {
	ostringstream ss;
	ss << fixed << setprecision(2) << obj;
	return ss.str().size();
}

string getHex(string str) {
	char buf[100] = {};
	string res;
	for (int i = 0; i < 6 && i < str.size(); ++i) {
		sprintf(buf, "%x ", (unsigned char)str.c_str()[i]);
		res = res + string(buf);
	}
	return res;
}

class Printer {
public:
    Printer() {}
    ~Printer(){}
    static void printHeader(std::vector<AttributeTree::AttributeDescriptor> attrs, bool limitWidth = false, std::ostream& c = std::cout) {
		Printer::attrLenSum = 0;
		if (limitWidth == false) {
			for (int i = 0; i < attrs.size(); ++i)
				if (attrs[i].relName.empty())
					Printer::attrLenSum += attrs[i].attrName.size() + 3;
				else
					Printer::attrLenSum += attrs[i].relName.size() + 1 + attrs[i].attrName.size() + 3;
			printBar(c);
			c << "| ";
			widths.clear();
			for (int i = 0; i < attrs.size(); ++i) {
				if (attrs[i].relName.empty()) {
					c << attrs[i].attrName << " | ";
					widths.push_back(attrs[i].attrName.size());
				}
				else {
					c << (attrs[i].relName + "." + attrs[i].attrName) << " | ";
					widths.push_back(attrs[i].relName.size() + 1 + attrs[i].attrName.size());
				}
			}
			c << endl;
		}
		else {  // ����޶�Ϊwidths[]
			for (int i = 0; i < attrs.size(); ++i)
				Printer::attrLenSum += widths[i] + 3;
			printBar(c);
			c << "| ";
			for (int i = 0; i < attrs.size(); ++i)
				if (attrs[i].relName.empty())
					c << setw(widths[i]) << attrs[i].attrName << " | ";
				else
					c << setw(widths[i]) << (attrs[i].relName + "." + attrs[i].attrName) << " | ";
			c << endl;
		}
		printBar(c);
	}

    static void printAll(std::vector<RecordDescriptor> recordDescriptors, std::vector<AttributeTree::AttributeDescriptor> *attrs = NULL, std::ostream& c = std::cout) {
		if (recordDescriptors.empty())
			return;

		int attrCount = 0;

		// ���widths ������widths[i]��ʾ��ǰ��i��������Ŀ������Ǹ��Ĵ�ӡ���
		widths.clear();
		if (attrs == NULL) {
			attrCount = recordDescriptors[0].attrNames.size();
			for (int i = 0; i < attrCount; ++i)
				widths.push_back(recordDescriptors[0].attrNames[i].size());
		}
		else {
			attrCount = attrs->size();
			for (int i = 0; i < attrCount; ++i) {
				int width;
				if (attrs->operator[](i).relName.empty())
					width = attrs->operator[](i).attrName.size();
				else
					width = attrs->operator[](i).attrName.size() + 1 + attrs->operator[](i).relName.size();
				widths.push_back(width);
			}
		}
		for (int i = 0; i < attrCount; ++i)
			for (const auto &recordDescriptor : recordDescriptors) {
				const auto &val = recordDescriptor.attrVals[i];
				int &width = widths[i];
				if (val.isNull)
					width = max(width, 4);
				else
					switch (val.type) {
					case T_INT:
						width = max(width, length(val.i));
						break;
					case T_FLOAT:
						width = max(width, length(val.f));
						break;
					case T_STRING:
						width = max(width, length(val.s));
						break;
					case T_DATE:
						width = max(width, length(val.s));
						break;
					case T_NONE:
						width = max(width, length(getHex(val.s)));
						break;
					}
			}

		// First Print Header
		if (attrs == NULL) {
			Printer::attrLenSum = 0;
			for (int i = 0; i < attrCount; ++i)
				Printer::attrLenSum += widths[i] + 3;
			printBar(c);
			c << "| ";
			for (int i = 0; i < attrCount; ++i)
				c << setw(widths[i]) << recordDescriptors[0].attrNames[i] << " | ";
			c << endl;
			printBar(c);
		}
		else
			printHeader(*attrs, true);
		for (const auto& recordDescriptor : recordDescriptors) {
			c << "| ";
			for (int i = 0; i < attrCount; ++i) {
				const auto& val = recordDescriptor.attrVals[i];
				int width = widths[i];
				if (val.isNull)
					c << setw(width) << "NULL" << " | ";
				else {
					switch (val.type) {
					case T_INT:
						c << setw(width) << val.i << " | ";
						break;
					case T_FLOAT:
						c << setw(width) << fixed << setprecision(2) << val.f << " | ";
						break;
					case T_STRING:
						c << setw(width) << val.s << " | ";
						break;
					case T_DATE:
						c << setw(width) << val.s << " | ";
						break;
					case T_NONE:
						c << setw(width) << getHex(val.s) << " | ";
						break;
					}
				}
			}
			c << endl;
		}
		printFooter(c);
		c << "Total = " << recordDescriptors.size() << " entries." << endl;
	}

    static void printFooter(std::ostream& c = std::cout) {
		printBar(c);
	}
    static std::vector<int> widths;

private:
    static void printBar(std::ostream &c = std::cout) {
		c << "+";
		for (int i = 0; i < Printer::attrLenSum - 1; ++i)
			c << "-";
		c << "+" << endl;
	}
    static int attrLenSum;
};
int Printer::attrLenSum;
vector<int> Printer::widths;



#endif //DATABASE_PRINTER_H
