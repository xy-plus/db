#pragma once
#include "Record.hpp"
#include "FileHandler.hpp"
#include "utils.h"
#include "Types.hpp"
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/MyHashMap.h"
#include <vector>
#include <string>

using namespace std;

struct Line
{
	string name;
	AttrType type;
	int maxLen;
	int tailLen;// numeric
	bool null;
	Type defaultValue;
	string foreign_table;
	string foreign_name;

	void getMetadata(uint* data, int& offset) {
		data[offset] = name.length();
		offset++;
		for (int i = 0; i < name.length(); ++i) {
			data[offset] = (uint)name[i];
			offset++;
		}
		data[offset] = (uint)type;
		offset++;
		data[offset] = maxLen;
		offset++;
		data[offset] = tailLen;
		offset++;
		if (null) {
			data[offset] = 1;
		}
		else {
			data[offset] = 0;
		}
		offset++;

		int len;
		defaultValue.toChars((char*)(data + offset + 1), len);
		data[offset] = len;
		offset++;
		offset = offset + (len / 4);
		if (len % 4 != 0)
			offset++;

		data[offset] = foreign_table.length();
		offset++;
		for (int i = 0; i < foreign_table.length(); ++i) {
			data[offset] = (uint)foreign_table[i];
			offset++;
		}

		data[offset] = foreign_name.length();
		offset++;
		for (int i = 0; i < foreign_name.length(); ++i) {
			data[offset] = (uint)foreign_name[i];
			offset++;
		}
	}

	void setMetadata(uint* data, int &offset) {
		int len, temp;
		name = "";
		len = data[offset];
		offset++;
		for (int i = 0; i < len; ++i) {
			char ch = (char)data[offset];
			offset++;
			name = name + ch;
		}
		type = (AttrType)data[offset];
		offset++;
		maxLen = data[offset];
		offset++;
		tailLen = data[offset];
		offset++;
		
		temp = data[offset];
		offset++;
		if (temp == 1) {
			null = true;
		}
		else {
			null = false;
		}

		len = data[offset];
		offset++;
		defaultValue.fromChars((char*)(data + offset), len);
		offset = offset + (len / 4);
		if (len % 4 != 0)
			offset++;

		foreign_table = "";
		len = data[offset];
		offset++;
		for (int i = 0; i < len; ++i) {
			char ch = (char)data[offset];
			offset++;
			foreign_table = foreign_table + ch;
		}

		foreign_name = "";
		len = data[offset];
		offset++;
		for (int i = 0; i < len; ++i) {
			char ch = (char)data[offset];
			offset++;
			foreign_name = foreign_name + ch;
		}
	}
};

class Table {
	// TODO : uodata record
public:
	Table(FileHandler* fileHandler) {
		this->fileHandler = fileHandler;
		lines.clear();
		exist.clear();
		num = 0;
		primaryKey.clear();
	}

	bool add_PrimaryKey(vector<string> pkey) {
		if (primaryKey.size() > 0) {
			return false;
		}

		bool ok = true;
		for (int i = 0; i < pkey.size(); ++i) {
			string linename = pkey[i];
			int lineno = getLineNumber(pkey);
			if (lineno = -1) {
				ok = false;
				break;
			}
			primaryKey.push_back(lineno);
		}
		for (int i = 0; i < primaryKey.size(); ++i)
			for (int j = i + 1; j < primaryKey.size(); ++j) {
				if (primaryKey[i] == primaryKey[j]) ok = false;
			}

		if (ok == false) {
			primaryKey.clear();
			return false;
		}
		// TODO : 主键需要建立索引
		saveMetadata();
		return true;
	}

	bool delete_PrimaryKey() {
		if (primaryKey.size() == 0) {
			// 没有主键
			return false;
		}
		// TODO : 是否需要删除索引
		primaryKey.clear();
		saveMetadata();
		return true;
	}

	bool add_Line(Line newLine) {
		for (int i = 0; i < lines.size(); ++i) {
			if ((exist[i]) && (lines[i].name == newLine.name)){
				// 和已有列重名
				return false;
			}
		}
		lines.push_back(newLine);
		exist.push_back(true);
		saveMetadata();
		// TODO : 修改数据表文件
		return true;
	}

	bool delete_Line(string linename) {
		int id = getLineNumber(linename);
		if (id == -1) {
			// 不存在列
			return false;
		}
		exist[id] = false;
		saveMetadata();
		// TODO : 修改数据表文件
		return true;
	}

	bool add_Foerign(string name, string ftname, string flname) {
		int id = getLineNumber(oldLine);
		if (id == -1) {
			// 不存在列
			return false;
		}
		Line line = lines[id];
		if (line.foreign_table != "") {
			// 已有外键
			return false;
		}
		line.foreign_table = ftname;
		line.foreign_name = flname;
		lines[id] = line;
		saveMetadata();
		return true;
	}

	bool delete_Foreign(string name) {
		int id = getLineNumber(oldLine);
		if (id == -1) {
			// 不存在列
			return false;
		}
		Line line = lines[id];
		if (line.foreign_table == "") {
			// 原外键为空
			return false;
		}
		line.foreign_table = "";
		line.foreign_name = "";
		lines[id] = line;
		saveMetadata();
		return true;
	}

	bool change_Line(string oldLine, Line newLine) {
		int id = getLineNumber(oldLine);
		if (id == -1) {
			// 不存在列
			return false;
		}
		lines[id] = newLine;
		saveMetadata();
		// TODO : 修改数据表文件
		return true;
	}

private:
	friend class TableManager;
	FileHandler* fileHandler;

	int num;
	vector<Line> lines;
	vector<bool> exist;
	vector<int> primaryKey;

	int getLineNumber(string name) {
		for (int i = 0; i < lines.size(); ++i) {
			if (exist[i] && (name == lines[i].name)) {
				num = i;
				return num;
			}
		}
		return -1;
	}

	void saveMetadata() {
		data = new char[4096];
		getMetadata(data);
		RecordID metaID(1, 0);
		fileHandler->modifyRecord(metaID, (BufType)data);
		delete[] data;
	}

	void setMetadata(uint* data) {
		num = (int)data[0];

		int len = data[1];
		int offset = 2;
		lines.clear();
		exist.clear();
		for (int i = 0; i < len; ++i) {
			Line tempLine;
			tempLine.setMetadata(data, offset);
			lines.push_back(tempLine);

			int temp = data[offset];
			offset++;
			if (temp == 1) {
				exist.push_back(true);
			}
			else {
				exist.push_back(false);
			}
		}
		
		len = data[offset];
		offset++;
		primaryKey.clear();
		for (int i = 0; i < len; ++i) {
			int temp = data[offset];
			primaryKey.push_back(temp);
			offset++;
		}
	}

	void getMetaData(uint* data) {
		data[0] = (uint)num;
		data[1] = (uint)lines.size();
		int offset = 2;
		for (int i = 0; i < lines.size(); ++i) {
			// lines
			lines[i].getMetadata(data, offset);
			// exist
			if (exist[i]) {
				data[offset] = 1;
			}
			else {
				data[offset] = 0;
			}
			offset++;
		}
		data[offset] = primaryKey.size();
		offset++;
		for (int i = 0; i < primaryKey.size(); ++i) {
			data[offset] = primaryKey[i];
			offset++;
		}
	}
};
