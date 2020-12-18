#include <assert.h>
#include "GlobalFileHandler.hpp"
#include "Record.hpp"
#include "test.hpp"
#include "parser/parser.tab.c"
#include "parser/lex.yy.c"
#include "SystemManager.h"
//#include "index/BTree.hpp"
//#include "index/IndexManager.hpp"

const char testFileName[] = "test.txt";

/*
void index_operator() {
	IndexManager indexManager(bpm, fm);

	// �����������ļ�����������Ӧ�кš���Ӧ�����͡���Ӧ�г��ȣ�Numeric�����㣩
	// attrType �� utils.h
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

	// ���������ļ�����������Ӧ�к�
	// ����һ��BTree�����ڶԾ�����������
	BTree* bTree;
	indexManager.open_index(filename, attrNo, bTree);

	// ������������
	{
		// ����һ����������ԭ�ļ��е�rid��������Ӧ�е�ֵvalue
		RecordID rid;
		rid.page = 1;
		rid.slot = 0;
		Type* tp = new IntType();
		((IntType*)tp)->setInt(0);
		vector<Type*> value;
		value.clear();
		value.push_back(tp);

		bTree->insert_Record(rid, value);

		// ����һ����������rid����rid��������ֵ��������ֵ
		RecordID newrid;
		rid.page = 2;
		rid.slot = 0;
		Type* tp2 = new IntType();
		((IntType*)tp2)->setInt(1);
		vector<Type*> newvalue;
		newvalue.clear();
		newvalue.push_back(tp2);

		bTree->update_Record(rid, newrid, value, newvalue);

		// Ѱ����������������ֵ����Ӧ����ֵ���������������utils.h��
		// ����Ϊ ����ֵ = tp2
		// ����ֵ�����з��������Ķ�����ԭ�ļ��е�rid
		vector<CmpOP> ops;
		ops.clear();
		ops.push_back(EQ);
		vector<Type*> target;
		newvalue.clear();
		newvalue.push_back(tp2);

		vector<RecordID> answer = bTree->find_Record(target, ops);

		// ɾ������������ֵ
		bTree->delete_Record(newvalue);

		// rebuildδʵ�֣���֪����ʲô���ܣ�
		bTree->rebuild();
	}



	// �ر�������BTree
	indexManager.close_index(bTree);

	// ɾ���������ļ�����������Ӧ�к�
	indexManager.delete_index(file, attrNo);
}
*/
//void test_type() {
//	freopen("answer.txt", "w", stdout);
//
//	Type* tp1 = new IntType();
//	((IntType*)tp1)->setInt(1);
//	Type* tp2 = new IntType();
//	((IntType*)tp2)->setInt(2);
//	char* buf;
//	int len;
//	tp1->toChars(buf, len);
//	for (int i = 0; i < len; ++i)
//		cout << buf[i];
//	cout << endl;
//	tp1->fromChars(buf, len);
//
//	delete[] buf;
//	delete tp1;
//	delete tp2;
//
//	fclose(stdout);
//}

void runSQL(const char *sql) {
    delete Tree::tree;
    Tree::tree = nullptr;
    yy_switch_to_buffer(yy_scan_string(sql));
    yyparse();
}

//int main() {
//	auto globalFH = GlobalFileHandler::instance();
//    int record_len = 300;
//    globalFH->createFile(testFileName, record_len);
//    FileHandler* fh = openFile(testFileName);
//    test_db(fh, record_len);
//
//	// index_opertaor();
//	//test_type();
//
//    //exit_db();
//    return 0;
//}
#define bufsize 10000
char charbuf[bufsize + 1];

int main(int argc, char** argv) {
	string buffer;
	string message;

	if (argc == 2) {
		for (int i = 1; i < argc; ++i) {
			FILE *fin = fopen(argv[i], "r");
			if (!fin) {
				cerr << "[ERROR] Can not open file <" << argv[i] << ">." << endl;
				return 0;
			}
			cerr << "[INFO] Start running file <" << argv[i] << ">." << endl;
			while (fgets(charbuf, bufsize, fin)) {
				if (strlen(charbuf) == 0) continue;
				charbuf[strlen(charbuf) - 1] = 0;
				message = string(charbuf);
				if (!message.empty()) {
					buffer += message;
					if (message[message.size() - 1] == ';') {
						runSQL(buffer.c_str());
						buffer.clear();
					}
				}
			}
			if (buffer.size() > 0)
				runSQL(buffer.c_str());
			fclose(fin);
		}
		return 0;
	}

	printf("\n>> ");
	while (getline(cin, message)) {
		if (!message.empty()) {
			if (message[message.size() - 1] == ';') {
				buffer += message;
				runSQL(buffer.c_str());
				buffer.clear();
				printf("\n>> ");
			}
			else
				buffer += message;
		}
	}
	SystemManager::resetInstance();
	return 0;
}