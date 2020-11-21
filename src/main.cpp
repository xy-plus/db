#include <iostream>
#include <assert.h>
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/MyHashMap.h"
#include "FileHandler.hpp"
#include "Record.hpp"
#include "test.hpp"
#include "utils.h"
#include "Types.hpp"
//#include "index/BTree.hpp"
//#include "index/IndexManager.hpp"
using namespace std;

const char testFileName[] = "test.txt";

FileManager* fm;
BufPageManager* bpm;

void init() {
    MyBitMap::initConst();
    fm = new FileManager();
    bpm = new BufPageManager(fm);
}

FileHandler* openFile(const char* filename) {
    int fileID;
    assert(fm->openFile(filename, fileID));
    return new FileHandler(bpm, fileID);
}

int createFile(const char* filename, unsigned recordLength) {
    fm->createFile(filename);
    int fileID;
    fm->openFile(filename, fileID);
    int index;
    MetadataPageInfo* metadata =
        (MetadataPageInfo*)bpm->allocPage(fileID, 0, index);
    bpm->markDirty(index);
    metadata->pageCount = 2;
    metadata->recordLength = recordLength;
    metadata->recordCount = 0;
    metadata->nextAvailPage = 1;
    metadata->pageSlotNumber = PAGE_SLOT_COUNT / recordLength;

    BufType secondPage = bpm->allocPage(fileID, 1, index);
    PageInfo* pg = (PageInfo*)secondPage;
    bpm->markDirty(index);
    pg->pageNumber = 1;
    pg->nextAvailPage = 0;
    fm->closeFile(fileID);

    return fileID;
}

void exit_db() {
    bpm->close();
    delete fm;
}
/*
void index_operator() {
	IndexManager indexManager(bpm, fm);

	// 创建索引：文件名、索引对应列号、对应列类型、对应列长度（Numeric另外算）
	// attrType 见 utils.h
	const char* filename = "test";

	vector<int> attrNo;
	vector<AttrType> attrType;
	vector<int> attrLen;
	attrNo.clear();
	attrNo.push_back(1);
	attrType.clear();
	attrType.push_back(INTEGER);
	attrLen.clear();
	attrLen.push_back(4);

	indexManager.create_index(filename, attrNo, attrType, attrLen);

	// 打开索引：文件名、索引对应列号
	// 返回一个BTree，用于对具体索引操作
	BTree* bTree;
	indexManager.open_index(filename, attrNo, bTree);

	// 具体索引操作
	{
		// 插入一条索引：在原文件中的rid、索引对应列的值value
		RecordID rid;
		rid.page = 1;
		rid.slot = 0;
		Type* tp = new IntType();
		((IntType*)tp)->setInt(0);
		vector<Type*> value;
		value.clear();
		value.push_back(tp);

		bTree->insert_Record(rid, value);

		// 更新一条索引：旧rid、新rid、旧索引值、新索引值
		RecordID newrid;
		rid.page = 2;
		rid.slot = 0;
		Type* tp2 = new IntType();
		((IntType*)tp2)->setInt(1);
		vector<Type*> newvalue;
		newvalue.clear();
		newvalue.push_back(tp2);

		bTree->update_Record(rid, newrid, value, newvalue);

		// 寻找满足条件的索引值：对应条件值、条件运算符（见utils.h）
		// 例子为 索引值 = tp2
		// 返回值是所有符合条件的对象在原文件中的rid
		vector<CmpOP> ops;
		ops.clear();
		ops.push_back(EQ);
		vector<Type*> target;
		newvalue.clear();
		newvalue.push_back(tp2);

		vector<RecordID> answer = bTree->find_Record(target, ops);

		// 删除索引：索引值
		bTree->delete_Record(newvalue);

		// rebuild未实现（不知道是什么功能）
		bTree->rebuild();
	}



	// 关闭索引：BTree
	indexManager.close_index(bTree);

	// 删除索引：文件名、索引对应列号
	indexManager.delete_index(file, attrNo);
}
*/
void test_type() {
	freopen("answer.txt", "w", stdout);

	Type* tp1 = new IntType();
	((IntType*)tp1)->setInt(1);
	Type* tp2 = new IntType();
	((IntType*)tp2)->setInt(2);
	char* buf;
	int len;
	tp1->toChars(buf, len);
	for (int i = 0; i < len; ++i)
		cout << buf[i];
	cout << endl;
	tp1->fromChars(buf, len);

	delete[] buf;
	delete tp1;
	delete tp2;

	fclose(stdout);
}

int main() {
    init();
    int record_len = 300;
    createFile(testFileName, record_len);
    FileHandler* fh = openFile(testFileName);
    test_db(fh, record_len);

	// index_opertaor();
	test_type();

    exit_db();
    return 0;
}
