#include <cstdlib>
#include <cstring>
#include <string>
#include <set>
#include <cstddef>
#include <cstdio>
#include <algorithm>
#include <dirent.h>
#include "SystemManager.h"
#include "FileScan.hpp"
#include "DBHandle.h"
#include "Printer.hpp"
#include "IndexManager.hpp"
#include "BTree.hpp"

#ifdef __APPLE__
#include <sys/stat.h>
#endif

using namespace std;

SystemManager* SystemManager::systemManager = nullptr;

SystemManager::SystemManager()
{
    recordManager = GlobalFileHandler::instance();
    hasOpenDB = false;
#ifdef __MINGW32__
    mkdir(kDefaultDBPosition);
    chdir(kDefaultDBPosition);
#else
    mkdir(kDefaultDBPosition, S_IRWXU | S_IRWXG | S_IXOTH);
    chdir(kDefaultDBPosition);
#endif
}


SystemManager::~SystemManager() {

}

int SystemManager::createDB(const char *dbName) {
    if(hasOpenDB) {
        closeDB();
    }
    
#ifdef __MINGW32__
    mkdir(dbName);
    RETURNIF(chdir(dbName));
#else
    mkdir(dbName, S_IRWXU | S_IRWXG | S_IXOTH);
    chdir(dbName);
#endif

    
    /*

    - RelCat:
        table名, table一条记录的长度, table的attr数量, table有多少行, table是否有主键
    - AttrCat:
        table名, attr名, attr在记录中的偏移, attr类型, attr长度, attr索引编号, 在主键中的排序编号, 是否非空, attr是否存在默认值, 默认值
    - FkCat:
        fk名, 从table, 主table, attr数, 从attr1, 从attr2，从attr3, 主attr1, 主attr2, 主attr3
    - IdxCat:
        idxName, table名, attr名

    */


    
    RETURNIF(recordManager->createFile(kDefaultRelCatName, sizeof(DataRelInfo)));
    FileHandler* fileHandle = recordManager->openFile(kDefaultRelCatName);
    DataRelInfo dataRelInfo;
    memset(&dataRelInfo, 0, sizeof(DataRelInfo));
    dataRelInfo.recordSize = sizeof(DataRelInfo);
    dataRelInfo.indexCount = 0;
    dataRelInfo.attrCount = 5;
    dataRelInfo.primaryCount = 0;
    strcpy(dataRelInfo.relName, kDefaultRelCatName);
    RecordID recordID = fileHandle->insertRecord((BufType)&dataRelInfo);

    memset(&dataRelInfo, 0, sizeof(DataRelInfo));
    dataRelInfo.recordSize = sizeof(DataAttrInfo);
    dataRelInfo.indexCount = 0;
    dataRelInfo.attrCount = 10;
    dataRelInfo.primaryCount = 0;
    strcpy(dataRelInfo.relName, kDefaultAttrCatName);
	fileHandle->insertRecord((BufType)&dataRelInfo);

    memset(&dataRelInfo, 0, sizeof(DataRelInfo));
    dataRelInfo.recordSize = sizeof(DataFkInfo);
    dataRelInfo.indexCount = 0;
    dataRelInfo.attrCount = 10;
    dataRelInfo.primaryCount = 0;
    strcpy(dataRelInfo.relName, kDefaultFkCatName);
	fileHandle->insertRecord((BufType)&dataRelInfo);

    memset(&dataRelInfo, 0, sizeof(DataRelInfo));
    dataRelInfo.recordSize = sizeof(DataIdxInfo);
    dataRelInfo.indexCount = 0;
    dataRelInfo.attrCount = 3;
    dataRelInfo.primaryCount = 0;
    strcpy(dataRelInfo.relName, kDefaultIdxCatName);
	fileHandle->insertRecord((BufType)&dataRelInfo);

    
    RETURNIF(recordManager->createFile(kDefaultFkCatName, sizeof(DataFkInfo)));
    fileHandle = recordManager->openFile(kDefaultFkCatName);

    
    RETURNIF(recordManager->createFile(kDefaultIdxCatName, sizeof(DataIdxInfo)));
    fileHandle = recordManager->openFile(kDefaultIdxCatName);

    
    
    RETURNIF(recordManager->createFile(kDefaultAttrCatName, sizeof(DataAttrInfo)));
    fileHandle = recordManager->openFile(kDefaultAttrCatName);

    DataAttrInfo dataAttrInfo;
    memset(&dataAttrInfo, 0, sizeof(DataAttrInfo));
    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultRelCatName);
    strcpy(dataAttrInfo.attrName, "relName");
    dataAttrInfo.offset = offsetof(DataRelInfo, relName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultRelCatName);
    strcpy(dataAttrInfo.attrName, "recordSize");
    dataAttrInfo.offset = offsetof(DataRelInfo, recordSize);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultRelCatName);
    strcpy(dataAttrInfo.attrName, "attrCount");
    dataAttrInfo.offset = offsetof(DataRelInfo, attrCount);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultRelCatName);
    strcpy(dataAttrInfo.attrName, "indexCount");
    dataAttrInfo.offset = offsetof(DataRelInfo, indexCount);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultRelCatName);
    strcpy(dataAttrInfo.attrName, "primaryCount");
    dataAttrInfo.offset = offsetof(DataRelInfo, primaryCount);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    
    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "relName");
    dataAttrInfo.offset = offsetof(DataAttrInfo, relName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = false;
    dataAttrInfo.notNull = false;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "attrName");
    dataAttrInfo.offset = offsetof(DataAttrInfo, attrName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "offset");
    dataAttrInfo.offset = offsetof(DataAttrInfo, offset);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "attrType");
    dataAttrInfo.offset = offsetof(DataAttrInfo, attrType);
    dataAttrInfo.attrLength = sizeof(AttrType);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "attrLength");
    dataAttrInfo.offset = offsetof(DataAttrInfo, attrLength);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "indexNo");
    dataAttrInfo.offset = offsetof(DataAttrInfo, indexNo);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "isPrimaryKey");
    dataAttrInfo.offset = offsetof(DataAttrInfo, isPrimaryKey);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "notNull");
    dataAttrInfo.offset = offsetof(DataAttrInfo, notNull);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "isDefault");
    dataAttrInfo.offset = offsetof(DataAttrInfo, isDefault);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultAttrCatName);
    strcpy(dataAttrInfo.attrName, "defaultVal");
    dataAttrInfo.offset = offsetof(DataAttrInfo, defaultVal);
    dataAttrInfo.attrLength = MAX_DEF + 1;
    dataAttrInfo.attrType = AttrType::T_NONE;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    
    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "fkName");
    dataAttrInfo.offset = offsetof(DataFkInfo, fkName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "serRelName");
    dataAttrInfo.offset = offsetof(DataFkInfo, serRelName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "masRelName");
    dataAttrInfo.offset = offsetof(DataFkInfo, masRelName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "attrCount");
    dataAttrInfo.offset = offsetof(DataFkInfo, attrCount);
    dataAttrInfo.attrLength = sizeof(int);
    dataAttrInfo.attrType = AttrType::T_INT;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
	fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "serAttr1Name");
    dataAttrInfo.offset = offsetof(DataFkInfo, serAttr1Name);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "serAttr2Name");
    dataAttrInfo.offset = offsetof(DataFkInfo, serAttr2Name);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "serAttr3Name");
    dataAttrInfo.offset = offsetof(DataFkInfo, serAttr3Name);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "masAttr1Name");
    dataAttrInfo.offset = offsetof(DataFkInfo, masAttr1Name);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "masAttr2Name");
    dataAttrInfo.offset = offsetof(DataFkInfo, masAttr2Name);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultFkCatName);
    strcpy(dataAttrInfo.attrName, "masAttr3Name");
    dataAttrInfo.offset = offsetof(DataFkInfo, masAttr3Name);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

    
    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultIdxCatName);
    strcpy(dataAttrInfo.attrName, "idxName");
    dataAttrInfo.offset = offsetof(DataIdxInfo, idxName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultIdxCatName);
    strcpy(dataAttrInfo.attrName, "relName");
    dataAttrInfo.offset = offsetof(DataIdxInfo, relName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

    memset(dataAttrInfo.relName, 0, MAX_NAME + 1);
    memset(dataAttrInfo.attrName, 0, MAX_NAME + 1);
    strcpy(dataAttrInfo.relName, kDefaultIdxCatName);
    strcpy(dataAttrInfo.attrName, "attrName");
    dataAttrInfo.offset = offsetof(DataIdxInfo, attrName);
    dataAttrInfo.attrLength = MAX_NAME + 1;
    dataAttrInfo.attrType = AttrType::T_STRING;
    dataAttrInfo.indexNo = 0;
    dataAttrInfo.isPrimaryKey = 0;
    dataAttrInfo.notNull = 0;
    fileHandle->insertRecord((BufType)&dataAttrInfo);

#ifdef __MINGW32__
    RETURNIF(chdir(kDefaultDBPosition));
#else
    chdir("..");
#endif

    return RETVAL_OK;
}

int SystemManager::dropDB(const char *dbName) {
    if(hasOpenDB && strcmp(currentDBName, dbName) == 0)
        RETURNIF(recordManager->closeFile());

#ifdef __MINGW32__
    char cmd[256] = "rmdir /s /q ";
    strcat(cmd, kDefaultDBPosition);
    strcat(cmd, dbName);
    system(cmd);
#else
    char cmd[256] = "rm -rf ";
    if (hasOpenDB) {
        chdir("..");
        hasOpenDB = false;
    }
    strcat(cmd, dbName);
    system(cmd);
    printf("[INFO] Drop database %s success.\n", dbName);
#endif
    return 0;
}

int SystemManager::openDB(const char *dbName) {
    if(hasOpenDB)
        closeDB();
    MSGIF(chdir(dbName), "[ERROR] Database does not exist.");
    printf("[INFO] Open database %s success.\n", dbName);
    hasOpenDB = true;
    strcpy(currentDBName, dbName);
    RETURNIF(dbHandle.refreshHandle());
    return 0;
}

int SystemManager::closeDB() {
    RETURNIF(recordManager->closeFile());
    hasOpenDB = false;
    memset(currentDBName, 0, MAX_NAME);
#ifdef __MINGW32__
    RETURNIF(chdir(".."));
#else
    chdir("..");
#endif
    return 0;
}

int SystemManager::createTable(const char *relName, int attrCount, AttrInfo *attributes) {
    if(!hasOpenDB) {
        cerr << "[ERROR] Please open DB first!" << endl;
        return RETVAL_ERR;
    }
    if (hasRelation(relName)){
        cerr << "[ERROR] There is a table named <" << relName << ">." << endl;
        return RETVAL_ERR;
    }
    RETURNIF(dbHandle.createTable(relName, attrCount, attributes));
    return RETVAL_OK;
}

int SystemManager::dropTable(const char *relName, bool check) {
    if(strcmp(relName, kDefaultRelCatName) == 0 || strcmp(relName, kDefaultAttrCatName) == 0 
        || strcmp(relName, kDefaultFkCatName) == 0 || strcmp(relName, kDefaultIdxCatName) == 0){
            cerr << "[ERROR] You cannot drop a system table." << endl;
            return RETVAL_ERR;
    }

    
    if (check){
        vector<string> fkNames;
        for (const auto &fk: dbHandle.foreignKeys){
            if (strcmp(relName, fk.masRelName) == 0){
                cerr << "[ERROR] This table is the master table of a foreign key. Please drop that foreign key first." << endl;
                return RETVAL_ERR;
            }
            if (strcmp(relName, fk.serRelName) == 0)
                fkNames.push_back(string(fk.fkName));
        }
        for (const auto &s: fkNames)
            RETURNIF(dropForeignKey(relName, s.c_str()));
    }

    
    vector<const char*> indexNames;
    for (int i = 0, lim = dbHandle.indexes.size(); i < lim; ++i)
        if (strcmp(dbHandle.indexes[i].relName, relName) == 0)
            indexNames.push_back(dbHandle.indexes[i].idxName);
    for (int i = 0, lim = indexNames.size(); i < lim; ++i)
        dropIndex(relName, indexNames[i]);

    RETURNIF(dbHandle.dropTable(relName));
    return RETVAL_OK;
}

int SystemManager::createIndex(string relName, Attribute attrName, string idxName) {
    if (!hasRelation(relName.c_str())){
        cerr << "[ERROR] No such relation." << endl;
        return RETVAL_ERR;
    }

    
    DataAttrInfo attrData;
    int attrCount;
    bool found = false;
    bool foundIndex = false;
    RecordID attrRecordID;
    for(int i = 0; i < dbHandle.attributes.size(); ++i) {
        if(dbHandle.attributes[i].attrName == attrName.attrName && dbHandle.attributes[i].relName == relName) {
            found = true;
            attrRecordID = dbHandle.attributeRecordIDs[i];
            attrData = dbHandle.attributes[i];
            if(dbHandle.attributes[i].indexNo != 0)
                foundIndex = true;
            break;
        }
    }
    if(!found) {
        cerr << "[ERROR] No such attribute to create index." << endl;
        return RETVAL_ERR;
    }
    if(foundIndex) {
        cerr << "[ERROR] Already have index for this attribute." << endl;
        return RETVAL_ERR;
    }
    if (hasIndex(relName.c_str(), idxName.c_str())){
        cerr << "[ERROR] Already have an index which has the same idxName on <" << relName << ">." << endl;
        return RETVAL_ERR;
    }

    
    int indexCount = 0;
    RecordID relRecordID;
    DataRelInfo relInfo;
    for(int i = 0; i < dbHandle.relations.size(); ++i) {
        const auto& dataRelInfo = dbHandle.relations[i];
        if(relName == string(dataRelInfo.relName)) {
            indexCount = dataRelInfo.indexCount;
            relRecordID = dbHandle.relationRecordIDs[i];
            relInfo = dataRelInfo;
        }
    }
    indexCount++;
    attrData.indexNo = indexCount;
    relInfo.indexCount = indexCount;
    

    
    FileHandler* fileHandle = recordManager->openFile(kDefaultAttrCatName);
    fileHandle->modifyRecord(relRecordID, (BufType)(&attrData));
    recordManager->closeFile();
    
    fileHandle = recordManager->openFile(kDefaultRelCatName);
    Record record1((uint*)(&relInfo), sizeof(DataRelInfo), relRecordID);
	fileHandle->modifyRecord(relRecordID, (BufType)(&relInfo));
	recordManager->closeFile();
    
    fileHandle = recordManager->openFile(kDefaultIdxCatName);
    RecordID rid;
    DataIdxInfo dataIdxInfo;
    strcpy(dataIdxInfo.idxName, idxName.c_str());
    strcpy(dataIdxInfo.attrName, attrName.attrName.c_str());
    strcpy(dataIdxInfo.relName, relName.c_str());
    fileHandle->insertRecord((BufType)&dataIdxInfo);
    recordManager->closeFile();

    dbHandle.refreshHandle();

	// TODO
	IndexManager* IM = new IndexManager(bpm, fm);
	vector<int> indexs;
	vector<AttrType> attrTypes;
	vector<int> attrLength;

	indexs.clear();
	attrTypes.clear();
	attrLengths.claer();

	indexs.push_back(indexCount);
	attrTypes.push_back(attrData.attrType);
	attrLengths.push_back(attrData.attrLength);

	bool ok = IM->create_index(relName.c_str(), indexs, attrTypes, attrLengths);
	BTree* btree;
	    
    int rc;
    auto records = retrieveRecords(relName, rc);
	IM->open_index(relName.c_str(), indexs, &btree);

    for (auto it = records.begin(); it != records.end(); ++it) {
        RecordID rid = it->first;
        RecordDescriptor r = it->second;
        AttrValue v = r[attrName.attrName];
        char* data;
        if(v.isNull)
            continue;
        data = (char*)v.getElementPointer();

		vector<Type> datas;
		Type temp;
		switch (attrData.attrType) {
		case T_INT:
			temp.setAttrType(INTEGER);
			temp.setInt(to_string(data));
			break;
		case T_FLOAT:
			temp.setAttrType(NUMERIC);
			temp.setNumericString(to_string(data));
			break;
		case T_STRING:
			temp.setAttrType(CHAR);
			temp.setVal(to_string(data));
			break;
		case T_DATE:
			temp.setAttrType(DATE);
			temp.setDate(to_string(data));
			break;
		case T_NONE:
			break;
		default:
		}
		datas.push_back(temp);
		btree->insert_Record(rid, datas);
    }
	delete btree;
	delete IM;
    return RETVAL_OK;
}

int SystemManager::dropIndex(string relName, string idxName) {
    /*
        删除一个索引分为3个部分
        1、 在attrcat中把indexNo部分清零
        2、 由于在relcat中，indexCount列表示的是“当前列一共创建过的索引个数”，并且创建新的索引需要使用该值以避免问题，所以不应该修改relcat中的值
        3、 删掉索引文件
        4、 在idxcat中删去对应行
    */
    if (!hasRelation(relName.c_str())){
        cerr << "[ERROR] No such relation." << endl;
        return RETVAL_ERR;
    }
    if (!hasIndex(relName.c_str(), idxName.c_str())){
        cerr << "[ERROR] No such index name." << endl;
        return RETVAL_ERR;
    }

    RecordID indexRID;
    char attrName[MAX_NAME + 1] = {};
    for (int i = 0, lim = dbHandle.indexes.size(); i < lim; ++i)
        if (strcmp(dbHandle.indexes[i].idxName, idxName.c_str()) == 0 && strcmp(dbHandle.indexes[i].relName, relName.c_str()) == 0){
            strcpy(attrName, dbHandle.indexes[i].attrName);
            indexRID = dbHandle.indexRecordIDs[i];
            break;
        }

    DataAttrInfo attrData;
    RecordID attrRID;
    for (int i = 0, lim = dbHandle.attributes.size(); i < lim; ++i)
        if (strcmp(dbHandle.attributes[i].attrName, attrName) == 0 && strcmp(dbHandle.attributes[i].relName, relName.c_str()) == 0){
            attrRID = dbHandle.attributeRecordIDs[i];
            attrData = dbHandle.attributes[i];
            break;
        }

    int indexNo = attrData.indexNo;
    
    attrData.indexNo = 0;
    FileHandler *GlobalFileHandler = recordManager->openFile(kDefaultAttrCatName);
    GlobalFileHandler->modifyRecord(attrRID, (BufType)(&attrData));
	recordManager->closeFile();
    
    // TODO
	IndexManager* IM = new IndexManager(bpm, fm);
	vector<int> indexs;

	indexs.clear();

	indexs.push_back(indexCount);
	bool ok = IM->delete_index(relName.c_str(), indexs);
	delete IM;


    GlobalFileHandler = recordManager->openFile(kDefaultIdxCatName);
    int pag, slt;
    indexRID.getPageID(pag);
    indexRID.getSlotID(slt);
    GlobalFileHandler->deleteRecord(indexRID);
    recordManager->closeFile();

    dbHandle.refreshHandle();
    return RETVAL_OK;
}

int SystemManager::load(const char *relName, const char *fileName) {
    return 0;
}

int SystemManager::help() {
    if(!hasOpenDB) {
        cerr << "[ERROR] Please open DB first." << endl;
        return RETVAL_ERR;
    }
    RETURNIF(dbHandle.help());
    return RETVAL_OK;
}

std::vector<std::vector<string>> SystemManager::qHelp()
{
    return dbHandle.qHelp();
}

int SystemManager::help(const char *relName) {
    if(!hasOpenDB) {
        cerr << "[ERROR] Please open DB first." << endl;
        return RETVAL_ERR;
    }
    RETURNIF(dbHandle.help(relName));
    return RETVAL_OK;
}

std::vector<std::vector<string> > SystemManager::qHelp(const char *relName)
{
    return dbHandle.qHelp(relName);
}

int SystemManager::set(const char *paramName, const char *value) {
    return 0;
}

SystemManager *SystemManager::instance() {
    if(systemManager != nullptr)
        return systemManager;
    systemManager = new SystemManager();
    return systemManager;
}

void SystemManager::resetInstance() {
    GlobalFileHandler::resetInstance();
}


int SystemManager::Select(vector<AttributeTree::AttributeDescriptor> attrs,
                        vector<std::string> rels,
                        vector<ComparisonTree::ComparisonDescriptor> coms) {
    int rc = RETVAL_OK;
    vector<RecordDescriptor> records = select(attrs, rels, coms, rc);
    RETURNIF(rc);
    if (attrs.empty()){
        int attrCount;
        DataAttrInfo* dataAttrInfo;
        for (auto rel : rels){
            RETURNIF(dbHandle.fillAttributesFromTable(rel.c_str(), attrCount, dataAttrInfo));
            for (int i = 0; i < attrCount; ++i)
                attrs.push_back(AttributeTree::AttributeDescriptor{string(rels.size()>1? rel : ""), string(dataAttrInfo[i].attrName)});
            delete[] dataAttrInfo;
        }
    }
    if(records.empty()) {
        Printer::printHeader(attrs);
        return RETVAL_OK;
    }
    Printer::printAll(records, &attrs);
    return RETVAL_OK;
}


/*
    SELECT <selector> FROM <tablelist> (WHERE <whereClause>)
    selector:   attrs
    tablelist:  rels
    whereClause:    coms
*/
vector<RecordDescriptor> SystemManager::select(std::vector<AttributeTree::AttributeDescriptor> attrs,
                        std::vector<std::string> rels,
                        std::vector<ComparisonTree::ComparisonDescriptor> coms, int& rc) {
    if (!checkRelations(rels)) {    
        rc = RETVAL_ERR;
        return vector<RecordDescriptor>();
    }
    if (!checkAttributes(attrs, rels)) {    
        rc = RETVAL_ERR;
        return vector<RecordDescriptor>();
    }
    if (!checkComparisons(coms, rels)) {    
        rc = RETVAL_ERR;
        return vector<RecordDescriptor>();
    }

    
    vector<Comparison> inrel_coms;
    vector<Comparison> crossrel_coms;
    for (const auto &com : coms)
        if (com.isAttrCmp == true && com.attr.relName != com.attr2.relName)
            crossrel_coms.push_back(com);   
        else
            inrel_coms.push_back(com);      

    
    
    vector<vector<RecordDescriptor>> validRecords;
    for (auto & rel : rels) {
        auto out = retrieveRecordsByIndex(rel, inrel_coms, rc);
        validRecords.push_back(out);
    }
    vector<RecordDescriptor> output;
    iterateCrossProduct(validRecords, attrs, rels, crossrel_coms, 0, output);
    return output;
}

/*
    得到表连接的笛卡尔积
*/
void SystemManager::iterateCrossProduct(vector<vector<RecordDescriptor>> &records,
                                        vector<AttributeTree::AttributeDescriptor> attrs,
                                        vector<string> &rels,
                                        vector<SystemManager::Comparison> &coms,
                                        int depth,
                                        vector<RecordDescriptor>& output) {
    static vector<RecordDescriptor> crossproduct;
    static vector<int> com_rels1;       
    static vector<int> com_rels2;

    
    if (depth == records.size()) {
        bool flag = true;
        for (int i = 0; i < coms.size(); ++i) {
            Comparison &com = coms[i];
            RecordDescriptor &attr1 = crossproduct[com_rels1[i]];
            RecordDescriptor &attr2 = crossproduct[com_rels2[i]];
            if (!compare(attr1[com.attr.attrName], attr2[com.attr2.attrName], com.op)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            
            RecordDescriptor recordDescriptor;
            if (!attrs.empty()) {
                for (const auto& record : crossproduct) {
                    RecordDescriptor rr = record.filteredByAttributeName(attrs);
                    recordDescriptor = recordDescriptor.concatenate(rr);
                }
            } else {
                for (const auto &record : crossproduct)
                    recordDescriptor = recordDescriptor.concatenate(record);
            }
            output.push_back(recordDescriptor);
        }
    } else {
        
        if (depth == 0) {
            crossproduct = vector<RecordDescriptor>(records.size());
            com_rels1 = vector<int>();
            com_rels2 = vector<int>();
            for (const auto &com : coms) {
                for (int i = 0; i < rels.size(); ++i) {
                    if (rels[i] == com.attr.relName)
                        com_rels1.push_back(i);
                    if (rels[i] == com.attr2.relName)
                        com_rels2.push_back(i);
                }
            }
        }
        for (const auto &record : records[depth]) {
            crossproduct[depth] = record;
            iterateCrossProduct(records, attrs, rels, coms, depth + 1, output);
        }
    }
}

/*
    向relName里插入一条Record，它的值列表为vals
    如果attrs == NULL，说明是直接插入全部数值
    否则只插入限定的attrs，其他的做非空判断，填入默认值

    如果主键存在索引，就在索引里找重复
    否则扫描文件，寻找是否有重复。如果没有才可插入
*/
int SystemManager::Insert(std::string relName, std::vector<std::string>* attrs, std::vector<AttrValue> vals, bool check) {
    if (!hasRelation(relName.c_str())) {
        cerr << "[ERROR] No such relation." << endl;
        return RETVAL_ERR;
    }
    int rc;
    RecordDescriptor descriptor;            
    if (attrs == NULL)
        descriptor = RecordDescriptor::createRecordDescriptor(relName, vals, rc);
    else
        descriptor = RecordDescriptor::createRecordDescriptor(relName, *attrs, vals, rc);
    if(rc != RETVAL_OK) return rc;

    
    DataAttrInfo *dataAttrInfo;
    vector<int> primaryKey;         
    int primaryCount;
    int attrCount;
    RETURNIF(dbHandle.fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo));

    for (int i = 0, lim = dbHandle.relations.size(); i < lim; ++i)
        if (strcmp(relName.c_str(), dbHandle.relations[i].relName) == 0){
            primaryCount = dbHandle.relations[i].primaryCount;
            break;
        }

    
    if (primaryCount > 0 && check){  
        for (int i = 1; i <= primaryCount; ++i)
            for (int j = 0; j < attrCount; ++j)
                if (dataAttrInfo[j].isPrimaryKey == i){
                    primaryKey.push_back(j);
                    break;
                }
        if (primaryCount == 1 && dataAttrInfo[primaryKey[0]].indexNo > 0){  
            int primaryKeyIndex = primaryKey[0];
            
            char *data = (char*)descriptor.attrVals[primaryKeyIndex].getElementPointer();

			// TODO
			IndexManager* IM = new IndexManager(bpm, fm);
			vector<int> indexs;
			indexs.clear();
			indexs.push_back(dataAttrInfo[primaryKeyIndex].indexNo);
			BTree* btree;
			IM->open_index(relName.c_str(), indexs, &btree);



			vector<Type> datas;
			Type temp;
			switch (attrData.attrType) {
			case T_INT:
				temp.setAttrType(INTEGER);
				temp.setInt(to_string(data));
				break;
			case T_FLOAT:
				temp.setAttrType(NUMERIC);
				temp.setNumericString(to_string(data));
				break;
			case T_STRING:
				temp.setAttrType(CHAR);
				temp.setVal(to_string(data));
				break;
			case T_DATE:
				temp.setAttrType(DATE);
				temp.setDate(to_string(data));
				break;
			case T_NONE:
				break;
			default:
			}
			datas.push_back(temp);
			vector<CmpOP> ops;
			ops.clear();
			ops.push_back(EQ);
			auto ret = btree->find_Record(datas, ops);

			delete btree;
			delete IM;

            if (ret.size() > 0){
                cerr << "[ERROR] Duplicated primary key values." << endl;
                return RETVAL_ERR;
            }
        }else{  
            vector<void*> values;
            vector<AttrType> types;
            vector<int> lengths;
            vector<int> offsets;
            for (int i = 0; i < primaryCount; ++i){
                types.push_back(dataAttrInfo[primaryKey[i]].attrType);
                lengths.push_back(dataAttrInfo[primaryKey[i]].attrLength);
                offsets.push_back(dataAttrInfo[primaryKey[i]].offset);
                values.push_back(descriptor.attrVals[primaryKey[i]].getElementPointer());
            }
            FileScan fileScan;
            FileHandler *fileHandle;
            fileHandle = GlobalFileHandler::instance()->openFile(relName.c_str());
            fileScan.openScan(*fileHandle, types, lengths, offsets, T_EQ, values);
            Record _;
            rc = fileScan.getNextRec(_);
            if (rc != RETVAL_EOF){
                cerr << "[ERROR] Duplicated primary key values." << endl;
                return RETVAL_ERR;
            }
        }
    }
    

    
    if (check){
        vector <DataFkInfo*> foreignKeys;   
        for (auto &fk: dbHandle.foreignKeys)
            if (strcmp(relName.c_str(), fk.serRelName) == 0)
                foreignKeys.push_back(&fk);
        for (auto &fk: foreignKeys){
            auto masRelName = fk->masRelName;
            auto serRelName = relName;
            auto fkAttrCount = fk->attrCount;
            vector<AttributeTree::AttributeDescriptor> masAttrs, serAttrs;
            if (fkAttrCount >= 1){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr1Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr1Name)});
            }
            if (fkAttrCount >= 2){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr2Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr2Name)});
            }
            if (fkAttrCount >= 3){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr3Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr3Name)});
            }
            
            auto record = descriptor.filteredByAttributeName(serAttrs, false);
            if (!existsRecord(masRelName, masAttrs, record.attrVals)){
                cerr << "[ERROR] Insertion will damage foreign-key data integrity constraints." << endl;
                return RETVAL_ERR;
            }
        }
    }
    

    FileHandler *fileHandle = GlobalFileHandler::instance()->openFile(relName.c_str());
    Record record;
    rc = descriptor.toRecord(RecordID(), record);
    if(rc != RETVAL_OK) return RETVAL_ERR;
    RecordID rid;
    fileHandle->insertRecord(record.getData());

    
    for(int i = 0; i < attrCount; ++i)
        if(dataAttrInfo[i].indexNo != 0) {
            
            AttrValue v = descriptor[dataAttrInfo[i].attrName];
            char* data;
            if(v.isNull)
                continue;
            data = (char*)v.getElementPointer();



			// TODO
			IndexManager* IM = new IndexManager(bpm, fm);
			vector<int> indexs;
			indexs.clear();
			indexs.push_back(dataAttrInfo[i].indexNo);
			BTree* btree;
			IM->open_index(relName.c_str(), indexs, &btree);

			vector<Type> datas;
			Type temp;
			switch (attrData.attrType) {
			case T_INT:
				temp.setAttrType(INTEGER);
				temp.setInt(to_string(data));
				break;
			case T_FLOAT:
				temp.setAttrType(NUMERIC);
				temp.setNumericString(to_string(data));
				break;
			case T_STRING:
				temp.setAttrType(CHAR);
				temp.setVal(to_string(data));
				break;
			case T_DATE:
				temp.setAttrType(DATE);
				temp.setDate(to_string(data));
				break;
			case T_NONE:
				break;
			default:
			}
			datas.push_back(temp);
			btree->insert_Record(rid, datas);

			delete btree;
			delete IM;
        }

    delete []dataAttrInfo;
    return RETVAL_OK;
}

int SystemManager::Update(std::string relName,
                        AttributeTree::AttributeDescriptor attr,
                        AttrValue val,
                        std::vector<ComparisonTree::ComparisonDescriptor> coms) {       
    vector<AttributeTree::AttributeDescriptor> attrs;
    vector<string> rels;
    attrs.push_back(attr);
    rels.push_back(relName);
    if (!checkRelations(rels)) {
        cerr << "[ERROR] Relation does not exist." << endl;
        return RETVAL_ERR;
    }
    if (!checkAttributes(attrs, rels)) {
        cerr << "[ERROR] Relation <" << relName << "> does not have attribute <" << attr.attrName << ">." << endl;
        return RETVAL_ERR;
    }
    if (!checkComparison(coms, relName)) {
        cerr << "[ERROR] Comparision invalid." << endl;
        return RETVAL_ERR;
    }

    int rc;
    auto records = retrieveRecords(relName, rc);
    if(rc != RETVAL_OK) {
        cerr << "[ERROR] Failed on retriving records." << endl;
        return RETVAL_ERR;
    }

    
    int attrCount = 0;
    DataAttrInfo* dataAttrInfo = nullptr;
    DataAttrInfo primaryAttrInfo;
    bool isPrimaryKey = false;
    RETURNIF(dbHandle.fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo));
    for(int i = 0; i < attrCount; ++i) {
        if(attr.attrName == string(dataAttrInfo[i].attrName)) {
            if(dataAttrInfo[i].isPrimaryKey) {
                isPrimaryKey = true;
                primaryAttrInfo = dataAttrInfo[i];
            }
            break;
        }
    }

    for(int i = 0; i < attrCount; ++i) {
        if(dataAttrInfo[i].attrName == attr.attrName) {
            AttrType t = dataAttrInfo[i].attrType;
            if(t != val.type) {
                cerr << "[ERROR] Attribute's types mismatch." << endl;
                return RETVAL_ERR;
            }
        }
    }

    vector<RecordDescriptor *> validRecords;
    RecordID recordID;
    FileHandler *fileHandle;

    vector <DataFkInfo*> fkAsMas, fkAsSer;
    for (auto &fk: dbHandle.foreignKeys){
        if (strcmp(relName.c_str(), fk.serRelName) == 0)
            fkAsSer.push_back(&fk);
        if (strcmp(relName.c_str(), fk.masRelName) == 0)
            fkAsMas.push_back(&fk);
    }

    for (auto it = begin(records); it != end(records); ++it) {
        if (isValid(coms, it->second, relName)) {   
            if(!isPrimaryKey) {     
                
                for(int i = 0; i < attrCount; ++i) {
                    if(dataAttrInfo[i].indexNo != 0 && dataAttrInfo[i].attrName == attr.attrName) {
                        AttrValue v = it->second[dataAttrInfo[i].attrName];
                        char* data;
                        if(v.isNull)
                            continue;
                        data = (char*)v.getElementPointer();


						// TODO
						IndexManager* IM = new IndexManager(bpm, fm);
						vector<int> indexs;
						indexs.clear();
						indexs.push_back(dataAttrInfo[i].indexNo);
						BTree* btree;
						IM->open_index(relName.c_str(), indexs, &btree);

						vector<Type> datas;
						Type temp;
						switch (attrData.attrType) {
						case T_INT:
							temp.setAttrType(INTEGER);
							temp.setInt(to_string(data));
							break;
						case T_FLOAT:
							temp.setAttrType(NUMERIC);
							temp.setNumericString(to_string(data));
							break;
						case T_STRING:
							temp.setAttrType(CHAR);
							temp.setVal(to_string(data));
							break;
						case T_DATE:
							temp.setAttrType(DATE);
							temp.setDate(to_string(data));
							break;
						case T_NONE:
							break;
						default:
						}
						datas.push_back(temp);
						btree->delete_Record(datas, it->first);

						delete btree;
						delete IM;
                    }
                }

                for (auto &fk: fkAsMas){
                    auto masRelName = fk->masRelName;
                    auto serRelName = fk->serRelName;
                    auto fkAttrCount = fk->attrCount;
                    vector<AttributeTree::AttributeDescriptor> masAttrs, serAttrs;
                    if (fkAttrCount >= 1){
                        masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr1Name)});
                        serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr1Name)});
                    }
                    if (fkAttrCount >= 2){
                        masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr2Name)});
                        serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr2Name)});
                    }
                    if (fkAttrCount >= 3){
                        masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr3Name)});
                        serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr3Name)});
                    }

                    auto record = it->second.filteredByAttributeName(masAttrs, false);
                    auto record_modify = it->second;
                    record_modify.assign(attr.attrName, val);
                    record_modify = record_modify.filteredByAttributeName(masAttrs, false);
                    if (existsRecord(serRelName, serAttrs, record.attrVals) && !existsRecord(serRelName, serAttrs, record_modify.attrVals)){
                        cerr << "[ERROR] Update will damage foreign-key data integrity constraints." << endl;
                        return RETVAL_ERR;
                    }
                }
                
                it->second.assign(attr.attrName, val);

                for (auto &fk: fkAsSer){
                    auto masRelName = fk->masRelName;
                    auto serRelName = fk->serRelName;
                    auto fkAttrCount = fk->attrCount;
                    vector<AttributeTree::AttributeDescriptor> masAttrs, serAttrs;
                    if (fkAttrCount >= 1){
                        masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr1Name)});
                        serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr1Name)});
                    }
                    if (fkAttrCount >= 2){
                        masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr2Name)});
                        serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr2Name)});
                    }
                    if (fkAttrCount >= 3){
                        masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr3Name)});
                        serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr3Name)});
                    }

                    auto record = it->second.filteredByAttributeName(serAttrs, false);
                    if (!existsRecord(masRelName, masAttrs, record.attrVals)){
                        cerr << "[ERROR] Update will damage foreign-key data integrity constraints." << endl;
                        return RETVAL_ERR;
                    }
                }

                Record record;
                rc = it->second.toRecord(it->first, record);
                if(rc != RETVAL_OK) {
                    cerr << "[ERROR] Inner error in toRecord()." << endl;
                    delete[] dataAttrInfo;
                    return RETVAL_ERR;
                }
                fileHandle = GlobalFileHandler::instance()->openFile(relName.c_str());
                fileHandle->modifyRecord(record.getRecordID(), record.getData());

                
                for(int i = 0; i < attrCount; ++i) {
                    if(dataAttrInfo[i].indexNo != 0 && dataAttrInfo[i].attrName == attr.attrName) {
                        AttrValue v = it->second[attr.attrName];
                        char* data;
                        if(v.isNull)
                            continue;
                        data = (char*)v.getElementPointer();


						// TODO
						IndexManager* IM = new IndexManager(bpm, fm);
						vector<int> indexs;
						indexs.clear();
						indexs.push_back(dataAttrInfo[i].indexNo);
						BTree* btree;
						IM->open_index(relName.c_str(), indexs, &btree);

						vector<Type> datas;
						Type temp;
						switch (attrData.attrType) {
						case T_INT:
							temp.setAttrType(INTEGER);
							temp.setInt(to_string(data));
							break;
						case T_FLOAT:
							temp.setAttrType(NUMERIC);
							temp.setNumericString(to_string(data));
							break;
						case T_STRING:
							temp.setAttrType(CHAR);
							temp.setVal(to_string(data));
							break;
						case T_DATE:
							temp.setAttrType(DATE);
							temp.setDate(to_string(data));
							break;
						case T_NONE:
							break;
						default:
						}
						datas.push_back(temp);
						btree->insert_Record(it->first, datas);

						delete btree;
						delete IM;
                    }
                }
            }
            else {  
                recordID = it->first;
                validRecords.push_back(&(it->second));
            }
        }
    }
    if(validRecords.empty());   
    else if(isPrimaryKey) {
        if(validRecords.size() > 1) {
            cerr << "[ERROR] Primary Key Duplicate!" << endl;
            delete[] dataAttrInfo;
            return RETVAL_ERR;
        }
        
        void* data = val.getElementPointer();

        FileScan fileScan;
        fileHandle = GlobalFileHandler::instance()->openFile(relName.c_str());
        fileScan.openScan(*fileHandle,
                        primaryAttrInfo.attrType,
                        primaryAttrInfo.attrLength,
                        primaryAttrInfo.offset,
                        CmpOP::T_EQ, data);
        Record record;
        rc = fileScan.getNextRec(record);
        if(rc != RETVAL_EOF) {
            cerr << "[ERROR] Primary Key Duplicate!" << endl;
            delete[] dataAttrInfo;
            return RETVAL_ERR;
        }
        
        for(int i = 0; i < attrCount; ++i) {
            if(dataAttrInfo[i].indexNo != 0 && dataAttrInfo[i].attrName == attr.attrName) {
                AttrValue v = (*(validRecords[0]))[attr.attrName];
                char* data;
                if(v.isNull)
                    continue;
                data = (char*)v.getElementPointer();

				// TODO
				IndexManager* IM = new IndexManager(bpm, fm);
				vector<int> indexs;
				indexs.clear();
				indexs.push_back(dataAttrInfo[i].indexNo);
				BTree* btree;
				IM->open_index(relName.c_str(), indexs, &btree);

				vector<Type> datas;
				Type temp;
				switch (attrData.attrType) {
				case T_INT:
					temp.setAttrType(INTEGER);
					temp.setInt(to_string(data));
					break;
				case T_FLOAT:
					temp.setAttrType(NUMERIC);
					temp.setNumericString(to_string(data));
					break;
				case T_STRING:
					temp.setAttrType(CHAR);
					temp.setVal(to_string(data));
					break;
				case T_DATE:
					temp.setAttrType(DATE);
					temp.setDate(to_string(data));
					break;
				case T_NONE:
					break;
				default:
				}
				datas.push_back(temp);
				btree->delete_Record(datas, recordID);

				delete btree;
				delete IM;
            }
        }

        
        for (auto &fk: fkAsMas){
            auto masRelName = fk->masRelName;
            auto serRelName = fk->serRelName;
            auto fkAttrCount = fk->attrCount;
            vector<AttributeTree::AttributeDescriptor> masAttrs, serAttrs;
            if (fkAttrCount >= 1){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr1Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr1Name)});
            }
            if (fkAttrCount >= 2){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr2Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr2Name)});
            }
            if (fkAttrCount >= 3){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr3Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr3Name)});
            }

            auto record = validRecords[0]->filteredByAttributeName(masAttrs, false);
            auto record_modify = *(validRecords[0]);
            record_modify.assign(attr.attrName, val);
            record_modify = record_modify.filteredByAttributeName(masAttrs, false);
            if (existsRecord(serRelName, serAttrs, record.attrVals) && !existsRecord(serRelName, serAttrs, record_modify.attrVals)){
                cerr << "[ERROR] Update will damage foreign-key data integrity constraints." << endl;
                return RETVAL_ERR;
            }
        }

        
        validRecords[0]->assign(attr.attrName, val);

        
        for (auto &fk: fkAsSer){
            auto masRelName = fk->masRelName;
            auto serRelName = fk->serRelName;
            auto fkAttrCount = fk->attrCount;
            vector<AttributeTree::AttributeDescriptor> masAttrs, serAttrs;
            if (fkAttrCount >= 1){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr1Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr1Name)});
            }
            if (fkAttrCount >= 2){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr2Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr2Name)});
            }
            if (fkAttrCount >= 3){
                masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr3Name)});
                serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr3Name)});
            }

            auto record = validRecords[0]->filteredByAttributeName(serAttrs, false);
            if (!existsRecord(masRelName, masAttrs, record.attrVals)){
                cerr << "[ERROR] Update will damage foreign-key data integrity constraints." << endl;
                return RETVAL_ERR;
            }
        }

        
        rc = validRecords[0]->toRecord(recordID, record);
        if(rc != RETVAL_OK) {
            cerr << "[ERROR] Inner error in toRecord()." << endl;
            delete[] dataAttrInfo;
            return RETVAL_ERR;
        }
        fileHandle = GlobalFileHandler::instance()->openFile(relName.c_str());
        fileHandle->modifyRecord(record.getRecordID(), record.getData());

        
        for(int i = 0; i < attrCount; ++i) {
            if(dataAttrInfo[i].indexNo != 0 && dataAttrInfo[i].attrName == attr.attrName) {
                AttrValue v = (*(validRecords[0]))[attr.attrName];
                char* data;
                if(v.isNull)
                    continue;
                data = (char*)v.getElementPointer();

				// TODO
				IndexManager* IM = new IndexManager(bpm, fm);
				vector<int> indexs;
				indexs.clear();
				indexs.push_back(dataAttrInfo[i].indexNo);
				BTree* btree;
				IM->open_index(relName.c_str(), indexs, &btree);

				vector<Type> datas;
				Type temp;
				switch (attrData.attrType) {
				case T_INT:
					temp.setAttrType(INTEGER);
					temp.setInt(to_string(data));
					break;
				case T_FLOAT:
					temp.setAttrType(NUMERIC);
					temp.setNumericString(to_string(data));
					break;
				case T_STRING:
					temp.setAttrType(CHAR);
					temp.setVal(to_string(data));
					break;
				case T_DATE:
					temp.setAttrType(DATE);
					temp.setDate(to_string(data));
					break;
				case T_NONE:
					break;
				default:
				}
				datas.push_back(temp);
				btree->delete_Record(datas, recordID);

				delete btree;
				delete IM;
            }
        }

    }
    delete[] dataAttrInfo;
    return RETVAL_OK;
}

int SystemManager::Delete(std::string relName, std::vector<ComparisonTree::ComparisonDescriptor> coms) {
    
    if (!hasRelation(relName.c_str())){
        cerr << "[ERROR] Relation <" << relName << "> does not exist." << endl;
        return RETVAL_ERR;
    }
    if (!checkComparison(coms, relName)){
        cerr << "[ERROR] Invalid where-clause." << endl;
        return RETVAL_ERR;
    }

    int rc;
    auto records = retrieveRecords(relName, rc);
    if(rc != RETVAL_OK) {
        cerr << "[ERROR] Error on retrieving records." << endl;
        return RETVAL_ERR;
    }

    int attrCount;
    DataAttrInfo* dataAttrInfo;
    RETURNIF(dbHandle.fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo));
    FileHandler *fileHandle = GlobalFileHandler::instance()->openFile(relName.c_str());

    vector <RecordDescriptor*> toBeDeleted;
    for (auto &rec: records)
        if (isValid(coms, rec.second, relName))
            toBeDeleted.push_back(&rec.second);

    vector <DataFkInfo*> foreignKeys;   
    for (auto &fk: dbHandle.foreignKeys)
        if (strcmp(relName.c_str(), fk.masRelName) == 0)
            foreignKeys.push_back(&fk);
    for (auto &fk: foreignKeys){
        auto masRelName = relName;
        auto serRelName = fk->serRelName;
        auto fkAttrCount = fk->attrCount;
        vector<AttributeTree::AttributeDescriptor> masAttrs, serAttrs;
        if (fkAttrCount >= 1){
            masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr1Name)});
            serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr1Name)});
        }
        if (fkAttrCount >= 2){
            masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr2Name)});
            serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr2Name)});
        }
        if (fkAttrCount >= 3){
            masAttrs.push_back(AttributeTree::AttributeDescriptor{string(masRelName), string(fk->masAttr3Name)});
            serAttrs.push_back(AttributeTree::AttributeDescriptor{string(serRelName), string(fk->serAttr3Name)});
        }

        
        for (auto &delEnt: toBeDeleted){
            auto record = delEnt->filteredByAttributeName(masAttrs, false);
            if (existsRecord(serRelName, serAttrs, record.attrVals)){
                cerr << "[ERROR] Deletion will damage foreign-key data integrity constraints." << endl;
                return RETVAL_ERR;
            }
        }
    }

    for (auto it = begin(records); it != end(records); ++it) {
        if (isValid(coms, it->second, relName)) {
            RecordID recordID = it->first;
            fileHandle->deleteRecord(recordID);
            
            for(int i = 0; i < attrCount; ++i) {
                if(dataAttrInfo[i].indexNo != 0) {
                    AttrValue v = it->second[dataAttrInfo[i].attrName];
                    char* data;
                    if(v.isNull)
                        continue;
                    data = (char*)v.getElementPointer();

					// TODO
					IndexManager* IM = new IndexManager(bpm, fm);
					vector<int> indexs;
					indexs.clear();
					indexs.push_back(dataAttrInfo[i].indexNo);
					BTree* btree;
					IM->open_index(relName.c_str(), indexs, &btree);

					vector<Type> datas;
					Type temp;
					switch (attrData.attrType) {
					case T_INT:
						temp.setAttrType(INTEGER);
						temp.setInt(to_string(data));
						break;
					case T_FLOAT:
						temp.setAttrType(NUMERIC);
						temp.setNumericString(to_string(data));
						break;
					case T_STRING:
						temp.setAttrType(CHAR);
						temp.setVal(to_string(data));
						break;
					case T_DATE:
						temp.setAttrType(DATE);
						temp.setDate(to_string(data));
						break;
					case T_NONE:
						break;
					default:
					}
					datas.push_back(temp);
					btree->delete_Record(datas, recordID);

					delete btree;
					delete IM;
                }
            }

        }
    }

    delete []dataAttrInfo;
    return 0;
}


bool SystemManager::checkRelations(const vector<string> &relations) {
    for (const auto &rel : relations)
        if (!hasRelation(rel.c_str())) {
            printf("No relation '%s'\n", rel.c_str());
            return false;
        }
    return true;
}

bool SystemManager::checkAttributes(vector<SystemManager::Attribute> &attributes, vector<string> &relations) {
    for (auto &attr : attributes)
        if (attr.relName.empty()) {
            int count = 0;
            for (const auto &rel : relations)
                if (hasAttribute(rel.c_str(), attr.attrName.c_str())) {
                    count += 1;
                    attr.relName = rel;
                }
            if (count == 0) {
                
                return false;
            } else if (count > 1) {
                
                return false;
            }
        } else {
            if (!hasRelation(attr.relName.c_str())) {
                
                return false;
            }
            if (!hasAttribute(attr.relName.c_str(), attr.attrName.c_str())) {
                
                return false;
            }
        }
    return true;
}


bool SystemManager::checkComparison(std::vector<Comparison> &coms, std::string &relation) {
    for (auto &com : coms) {
        if (com.attr.relName.empty() || com.attr.relName == relation) {
            if (!hasAttribute(relation.c_str(), com.attr.attrName.c_str())) {
                
                return false;
            }
            if (com.attr.relName.empty())
                com.attr.relName = relation;
        } else {
            
            return false;
        }
    }
    return true;
}

bool SystemManager::checkComparisons(vector<SystemManager::Comparison> &coms, vector<string> &relations) {
    for (auto &com : coms) {
        if (com.attr.relName.empty()) {
            int count = 0;
            for (const auto &rel : relations) {
                if (hasAttribute(rel.c_str(), com.attr.attrName.c_str())) {
                    count += 1;
                    com.attr.relName = rel;
                }
            }
            if (count == 0) {
                printf("Not found attribute '%s'\n", com.attr.attrName.c_str());
                return false;
            } else if (count > 1) {
                printf("Too many attribute named '%s'\n", com.attr.attrName.c_str());
                return false;
            }
        } else {
            bool exist = false;
            for (const auto &rel : relations)
                if (rel == com.attr.relName)
                    exist = true;
            if (!exist) {
                printf("In where clause, '%s' is not in relation list", com.attr.relName.c_str());
                return false;
            }
            if (!hasAttribute(com.attr.relName.c_str(), com.attr.attrName.c_str())) {
                printf("No attribute '%s', in relation '%s'\n", com.attr.attrName.c_str(), com.attr.relName.c_str());
                return false;
            }
        }

        if (com.isAttrCmp) {
            if (com.attr2.relName.empty()) {
                int count = 0;
                for (const auto &rel : relations) {
                    if (hasAttribute(rel.c_str(), com.attr2.attrName.c_str())) {
                        count += 1;
                        com.attr2.relName = rel;
                    }
                }
                if (count == 0) {
                    printf("Not found attribute '%s'\n", com.attr2.attrName.c_str());
                    return false;
                } else if (count > 1) {
                    printf("Too many attribute named '%s'\n", com.attr2.attrName.c_str());
                    return false;
                }
            } else {
                bool exist = false;
                for (const auto &rel : relations)
                    if (rel == com.attr2.relName)
                        exist = true;
                if (!exist) {
                    printf("In where clause, '%s' is not in relation list", com.attr2.relName.c_str());
                    return false;
                }
                if (!hasAttribute(com.attr2.relName.c_str(), com.attr2.attrName.c_str())) {
                    printf("No attribute '%s', in relation '%s'\n", com.attr2.attrName.c_str(), com.attr2.relName.c_str());
                    return false;
                }
            }
        }
    }
    return true;
}

/*
    检查relation表中，record是否满足条件coms
    只检查单表的coms
    包含NULL的判断，但不含主键的判断
*/
bool SystemManager::isValid(vector<SystemManager::Comparison> &coms, RecordDescriptor &record, const string &relation) {
    for (auto const &com : coms)
        if (!com.isAttrCmp && com.attr.relName == relation) {
            auto value = record[com.attr.attrName];
            if(com.op == T_ISNULL) {
                if(value.isNull)
                    return true;
                else
                    return false;
            }
            else if (com.op == T_ISNOTNULL){
                if(value.isNull)
                    return false;
                else
                    return true;
            }
            else if ((value.type == AttrType::T_INT || value.type == AttrType::T_FLOAT)
                && (com.val.type == AttrType::T_INT || com.val.type == AttrType::T_FLOAT)) {
                float f1 = value.type == AttrType::T_INT ? value.i : value.f;
                float f2 = com.val.type == AttrType::T_INT ? com.val.i : com.val.f;
                if (!compare(f1, f2, com.op))
                    return false;
            } else if (value.type == AttrType::T_STRING && com.val.type == AttrType::T_STRING) {
                if (!compare(value.s, com.val.s, com.op))
                    return false;
            } else if (value.type == AttrType::T_DATE && com.val.type == AttrType::T_DATE) {
                if (!compare(value.s, com.val.s, com.op))
                    return false;
            } else {
                cerr << "[ERROR] Incompatible types." << endl;
                return false;
            }
        }
    
    return true;
}

int SystemManager::qUpdate(const std::string& relName, const RecordID &recordID,
                        int attrNo, const AttrValue &newVal) {
    
    int rc = RETVAL_OK;
    RecordDescriptor recordDescriptor = dbHandle.retrieveOneRecord(relName, recordID, rc);
    RETURNIF(rc);
    recordDescriptor.attrVals[attrNo] = newVal;
    Record record;
    rc = recordDescriptor.toRecord(recordID, record);
    RETURNIF(rc);
    FileHandler* fileHandle = recordManager->openFile(relName.c_str());
    fileHandle->modifyRecord(record.getRecordID(), record.getData());
    recordManager->closeFile();
    return 0;
}

/*
    根据表名、约束名获得查找表项
    coms: 如 tablea.attr1 op constant
    首先找到其中的一列，这一列是和常量的比较，所以可以通过索引进行初筛
    如果没有这种列，就先把所有的行都取出
    接着进行暴力筛选
*/
vector<RecordDescriptor> SystemManager::retrieveRecordsByIndex(string relName,
                                                            const vector<SystemManager::Comparison> &coms,
                                                            int &rc) {
    
    int attrCount;
    DataAttrInfo* dataAttrInfo;
    dbHandle.fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo);     
    map<string, int> indexNoMap;
    for(int i = 0; i < attrCount; ++i) {
        
        indexNoMap[string(dataAttrInfo[i].attrName)] = dataAttrInfo[i].indexNo;
    }

    vector<RecordDescriptor> validRecords;
    vector<RecordDescriptor> output;
    int i = 0;
    for(i = 0; i < coms.size(); ++i) {
        const auto& com = coms[i];
        if (com.attr.relName != relName)
            continue;
        if(!com.isAttrCmp && com.op != T_ISNULL && com.op != T_ISNOTNULL &&
                indexNoMap[com.attr.attrName] != 0) {   
            
            AttrValue v = com.val;
            char* data;
            if(v.isNull)
                continue;
            data = (char*)v.getElementPointer();

			// TODO
			IndexManager* IM = new IndexManager(bpm, fm);
			vector<int> indexs;
			indexs.clear();
			indexs.push_back(indexNoMap[com.attr.attrName]);
			BTree* btree;
			IM->open_index(relName.c_str(), indexs, &btree);
			
			vector<Type> datas;
			Type temp;
			switch (attrData.attrType) {
			case T_INT:
				temp.setAttrType(INTEGER);
				temp.setInt(to_string(data));
				break;
			case T_FLOAT:
				temp.setAttrType(NUMERIC);
				temp.setNumericString(to_string(data));
				break;
			case T_STRING:
				temp.setAttrType(CHAR);
				temp.setVal(to_string(data));
				break;
			case T_DATE:
				temp.setAttrType(DATE);
				temp.setDate(to_string(data));
				break;
			case T_NONE:
				break;
			default:
			}
			datas.push_back(temp);
			vector<CmpOP> ops;
			ops.clear();
			ops.push_back(com.op);
			auto ret = btree->find_Record(datas, ops);

			delete btree;
			delete IM;

            FileHandler *f = GlobalFileHandler::instance()->openFile(relName.c_str());
            for(const auto& rid : ret) {
                Record rrr;
                f->getRecordById(rid, rrr);
                char* pData = (char*)rrr.getData();
                RecordDescriptor recordDescriptor;
                
                for(int i = 0; i < attrCount; ++i) {
                    AttrValue descriptor;
                    int offset = dataAttrInfo[i].offset;

                    AttrType attrType = dataAttrInfo[i].attrType;
                    if(attrType == T_INT) {
                        int data = ((int*)(pData+offset))[0];
                        descriptor.i = data;
                    } else if(attrType == T_FLOAT) {
                        float data = ((float*)(pData+offset))[0];
                        descriptor.f = data;
                    } else {
                        int attrLength = dataAttrInfo[i].attrLength;
                        char *data = new char[attrLength];
                        memset(data, 0, attrLength);
                        memcpy(data, pData + offset, attrLength);
                        descriptor.s = string(data);
                    }
                    descriptor.type = attrType;
                    recordDescriptor.attrNames.push_back(dataAttrInfo[i].attrName);
                    recordDescriptor.attrVals.push_back(descriptor);
                }
                int nullVectorBase = dataAttrInfo[attrCount-1].offset + dataAttrInfo[attrCount-1].attrLength;
                for(int i = 0; i < attrCount; ++i) {
                    char t;
                    memcpy((void*)&t, pData + nullVectorBase + i, 1);
                    if(t == 1 && relName != string(kDefaultAttrCatName) && relName != string(kDefaultRelCatName))
                        recordDescriptor.attrVals[i].isNull = true;
                    else
                        recordDescriptor.attrVals[i].isNull = false;
                }
                recordDescriptor.relName = relName;
                validRecords.push_back(recordDescriptor);
            }

            break;
        }
    }
    if(i == coms.size()) {
        
        auto records = retrieveRecords(relName, rc);
        for (auto it = begin(records); it != end(records); ++it) {
            validRecords.push_back(it->second);
        }
    }
    for(int j = 0; j < validRecords.size(); ++j) {
        bool flag = true;
        auto record = validRecords[j];
        for(int k = 0; k < coms.size(); ++k) {
            if(k == i)
                continue;   
            const auto& com = coms[k];
            if (com.attr.relName != relName)
                continue;
            if (!com.isAttrCmp) {
                if(record[com.attr.attrName].isNull && com.op == T_ISNULL) {
                    flag &= true;
                }
                else if(record[com.attr.attrName].isNull) {
                    flag = false;
                }
                else 
                    flag &= compare(record[com.attr.attrName], com.val, com.op);
            } else {
                flag &= compare(record[com.attr.attrName], record[com.attr2.attrName], com.op);
            }
            if (!flag) {
                break;
            }
        }
        if (flag) {
            output.push_back(record);
        }
    }
    delete []dataAttrInfo;
    return output;
}

/*
    给表relName添加一个主键，其主键项为attrs
*/
int SystemManager::addPrimaryKey(const char *relName, std::vector<std::string> attrs){
    if (!hasRelation(relName)){
        cerr << "[ERROR] Relation <" << relName << "> does not exist." << endl;
        return RETVAL_ERR;
    }
    for (const auto &s : attrs)
        if (!hasAttribute(relName, s.c_str())){
            cerr << "[ERROR] Relation <" << relName << "> does not have attribute <" << s << ">." << endl;
            return RETVAL_ERR;
        }

    
    for (int i = 0, limi = dbHandle.relations.size(); i < limi; ++i)
        if (strcmp(relName, dbHandle.relations[i].relName) == 0)
            if (dbHandle.relations[i].primaryCount > 0){
                cerr << "[ERROR] Relation <" << relName << "> already has a primary key." << endl;
                return RETVAL_ERR;
            }

    
    int rc, primaryCount = attrs.size(), recordCount = 0;
    auto records = retrieveRecords(string(relName), rc);
    DataAttrInfo *dataAttrInfo;
    int attrCount;
    RETURNIF(fillAttributesFromTable(relName, attrCount, dataAttrInfo));
    vector<int> primaryKeyIndexes;  
    for (const auto &s : attrs)
        for (int i = 0; i < attrCount; ++i)
            if (strcmp(s.c_str(), dataAttrInfo[i].attrName) == 0){
                primaryKeyIndexes.push_back(i);
                break;
            }

    
    for (const auto &record: records)
        for (const auto &idx: primaryKeyIndexes)
            if (record.second.attrVals[idx].isNull){
                cerr << "[ERROR] There is at least one NULL value in given attributes. Primary key requires NOT NULL." << endl;
                return RETVAL_ERR;
            }

    
    vector<vector<AttrValue> > recordValues;    
    for (const auto &record: records){
        recordValues.push_back(vector<AttrValue>());
        for (int j = 0; j < primaryCount; ++j)
            recordValues[recordCount].push_back(record.second.attrVals[primaryKeyIndexes[j]]);
        recordCount++;
    }
    sort(recordValues.begin(), recordValues.end());
    for (int i = 1; i < recordCount; ++i)
        if (recordValues[i-1] == recordValues[i]){
            cerr << "[ERROR] There are duplicated values in given attributes. Primary key requires unique values." << endl;
            return RETVAL_ERR;
        }

    

    
    RecordID relRID;
    DataRelInfo relData;
    for (int i = 0, limi = dbHandle.relations.size(); i < limi; ++i)
        if (strcmp(dbHandle.relations[i].relName, relName) == 0){
            relRID = dbHandle.relationRecordIDs[i];
            relData = dbHandle.relations[i];
            break;
        }
    relData.primaryCount = primaryCount;
    FileHandler *fileHandle = recordManager->openFile(kDefaultRelCatName);
    fileHandle->modifyRecord(relRID, (BufType)(&relData));
    recordManager->closeFile();

    
    for (int i = 0; i < primaryCount; ++i){
        int idx = -1;
        for (int j = 0, limj = dbHandle.attributes.size(); j < limj; ++j)
            if (strcmp(dbHandle.attributes[j].relName, relName) == 0 && strcmp(dbHandle.attributes[j].attrName, attrs[i].c_str()) == 0){
                idx = j;
                break;
            }
        if (idx == -1){
            cerr << "[ERROR] Attribute <" << attrs[i] << "> not found in relation." << endl;
            return RETVAL_ERR;
        }
        RecordID attrRID = dbHandle.attributeRecordIDs[idx];
        DataAttrInfo attrData = dbHandle.attributes[idx];
        attrData.isPrimaryKey = i + 1;
        attrData.notNull = 1;
        FileHandler *fileHandle = recordManager->openFile(kDefaultAttrCatName);
        fileHandle->modifyRecord(attrRID, (BufType)(&attrData));
        recordManager->closeFile();
    }

    dbHandle.refreshHandle();
    return RETVAL_OK;
}

int SystemManager::dropPrimaryKey(const char *relName){
    if (!hasRelation(relName)){
        cerr << "[ERROR] Relation <" << relName << "> does not exist." << endl;
        return RETVAL_ERR;
    }

    
    for (int i = 0, limi = dbHandle.relations.size(); i < limi; ++i)
        if (strcmp(relName, dbHandle.relations[i].relName) == 0)
            if (dbHandle.relations[i].primaryCount == 0){
                cerr << "[ERROR] Relation <" << relName << "> does not have a primary key." << endl;
                return RETVAL_ERR;
            }
    
    
    for (const auto &fk: dbHandle.foreignKeys)
        if (strcmp(fk.masRelName, relName) == 0){
            cerr << "[ERROR] This primary key is the master key of some certain foreign keys." << endl;
            return RETVAL_ERR;
        }

    

    
    RecordID relRID;
    DataRelInfo relData;
    for (int i = 0, limi = dbHandle.relations.size(); i < limi; ++i)
        if (strcmp(dbHandle.relations[i].relName, relName) == 0){
            relRID = dbHandle.relationRecordIDs[i];
            relData = dbHandle.relations[i];
            break;
        }
    relData.primaryCount = 0;
    FileHandler *fileHandle = recordManager->openFile(kDefaultRelCatName);
    fileHandle->modifyRecord(relRID, (BufType)(&relData));
    recordManager->closeFile();

    
    for (int i = 0, limi = dbHandle.attributes.size(); i < limi; ++i)
        if (strcmp(dbHandle.attributes[i].relName, relName) == 0 && dbHandle.attributes[i].isPrimaryKey > 0){
            RecordID attrRID = dbHandle.attributeRecordIDs[i];
            DataAttrInfo attrData = dbHandle.attributes[i];
            attrData.isPrimaryKey = 0;
            attrData.notNull = 0;
            FileHandler *fileHandle = recordManager->openFile(kDefaultAttrCatName);
            fileHandle->modifyRecord(attrRID, (BufType)(&attrData));
            recordManager->closeFile();
        }

    dbHandle.refreshHandle();
    return RETVAL_OK;
}

int SystemManager::getPrimaryKeyList(const char *relName, vector<string> &plist){
    if (!hasRelation(relName)){
        cerr << "[ERROR] Relation <" << relName << "> does not exist." << endl;
        return RETVAL_ERR;
    }
    plist.clear();
    for (int i = 0, limi = dbHandle.attributes.size(); i < limi; ++i)
        if (strcmp(relName, dbHandle.attributes[i].relName) == 0)
            if (dbHandle.attributes[i].isPrimaryKey > 0)
                plist.push_back(string(dbHandle.attributes[i].attrName));
    return RETVAL_OK;
}

bool operator < (const vector<AttrValue> &a, const vector<AttrValue> &b) {
    if (a.size() != b.size()) return false;
    int len = a.size();
    for (int i = 0; i < len; ++i){
        if (a[i] < b[i]) return true;
        if (a[i] > b[i]) return false;
    }
    
    return false;
}
bool operator == (const vector<AttrValue> &a, const vector<AttrValue> &b) {
    if (a.size() != b.size()) return false;
    int len = a.size();
    for (int i = 0; i < len; ++i)
        if (a[i] != b[i]) return false;
    
    return true;
}

/*
    插入一个外键
    如果checked为真，表示已经确保插入的合法性
*/
int SystemManager::addForeignKey(const char *fkName, 
    const char *serRelName, const char *masRelName, 
    std::vector<AttributeTree::AttributeDescriptor> &serAttrs, std::vector<AttributeTree::AttributeDescriptor> &masAttrs, bool checked){

    int rc;
    if (!checked){
        if (serAttrs.size() != masAttrs.size()){
            cerr << "[ERROR] The lengths of column lists from servant table and master table should be equal." << endl;
            return RETVAL_ERR;
        }
        int attrCount;
        DataAttrInfo *attrInfos;
        rc = fillAttributesFromTable(serRelName, attrCount, attrInfos);
        if (rc != RETVAL_OK){
            cerr << "[ERROR] Table name incorrect." << endl;
            return RETVAL_ERR;
        }
        
        for (const auto &fkattr: serAttrs){
            bool flag = false; 
            for (int i = 0; i < attrCount; ++i)
                if (fkattr.attrName == string(attrInfos[i].attrName)){
                    flag = true;
                    break;
                }
            if (!flag){
                cerr << "[ERROR] <" << fkattr.attrName << "> is not an attribute in this table." << endl;
                return RETVAL_ERR;
            }
        }
        
        for (int i = 0, limi = serAttrs.size(); i < limi; ++i)
            for (int j = i + 1; j < limi; ++j)
                if (serAttrs[i].attrName == serAttrs[j].attrName ||
                    masAttrs[i].attrName == masAttrs[j].attrName){
                        cerr << "[ERROR] Duplicated attributes in foreign key setting clause." << endl;
                        return RETVAL_ERR;
                    }
        
        vector<string> masPrimaryKeyList;
        int rc = getPrimaryKeyList(masRelName, masPrimaryKeyList);
        if (rc != RETVAL_OK) return rc;
        for (const auto &fkattr: masAttrs){
            bool found = false;
            for (const auto &attr: masPrimaryKeyList)
                if (attr == fkattr.attrName){
                    found = true;
                    break;
                }
            if (!found){
                cerr << "[ERROR] <" << fkattr.attrName << "> is not one of the primary key of the master table." << endl;
                return RETVAL_ERR;
            }
        }
        if (masAttrs.size() != masPrimaryKeyList.size()){
            cerr << "[ERROR] The attributes provided is not a primary key of the master table." << endl;
            return RETVAL_ERR;
        }
        
        vector<DataFkInfo> flist;
        getForeignKeyList(flist);
        for (const auto &fkInfo: flist)
            if (strcmp(fkInfo.fkName, fkName) == 0 && strcmp(fkInfo.serRelName, serRelName) == 0) {
                cerr << "[ERROR] Foreign key named <" << fkInfo.fkName << "> on table <" << serRelName << "> already exists." << endl;
                return RETVAL_ERR;
            }
        
        if (serAttrs.size() > 3){
            cerr << "[ERROR] Foreign keys should have no more than 3 attributes." << endl;
            return RETVAL_ERR;
        }
        
        for (int i = 0, limi = masAttrs.size(); i < limi; ++i){
            int rc;
            DataAttrInfo m;
            rc = SystemManager::instance()->getAttributeInfo(masRelName, masAttrs[i].attrName.c_str(), m);
            if (rc != RETVAL_OK){
                cerr << "[ERROR] Cannot find attribute <" << masAttrs[i].attrName << "> in master table." << endl;
                return RETVAL_ERR;
            }
            string serAttrName = serAttrs[i].attrName;
            AttrType stype = T_NONE;
            for (int j = 0; j < attrCount; ++j)
                if (string(attrInfos[j].attrName) == serAttrName){
                    stype = attrInfos[j].attrType;
                    break;
                }
            if (m.attrType != stype){
                cerr << "[ERROR] Foreign key types mismatch." << endl;
                return RETVAL_ERR;
            }
        }

        
        
        auto records = retrieveRecords(string(serRelName), rc);
        if (rc != RETVAL_OK){
            cerr << "[ERROR] Error when retrieving records." << endl;
            return RETVAL_ERR;
        }
        for (const auto &recpair: records){
            auto record = recpair.second.filteredByAttributeName(serAttrs, false);
            if (!existsRecord(masRelName, masAttrs, record.attrVals)){
                cerr << "[ERROR] In servant table, there are some entries do not satisfy data integrity constraints." << endl;
                return RETVAL_ERR;
            }
        }

        
    }
    
    
    FileHandler* fileHandle = recordManager->openFile(kDefaultFkCatName);
    DataFkInfo dataFkInfo;
    memset(&dataFkInfo, 0, sizeof(DataFkInfo));
    strcpy(dataFkInfo.fkName, fkName);
    strcpy(dataFkInfo.serRelName, serRelName);
    strcpy(dataFkInfo.masRelName, masRelName);
    dataFkInfo.attrCount = serAttrs.size();
    if (dataFkInfo.attrCount >= 1){
        strcpy(dataFkInfo.masAttr1Name, masAttrs[0].attrName.c_str());
        strcpy(dataFkInfo.serAttr1Name, serAttrs[0].attrName.c_str());
    }
    if (dataFkInfo.attrCount >= 2){
        strcpy(dataFkInfo.masAttr2Name, masAttrs[1].attrName.c_str());
        strcpy(dataFkInfo.serAttr2Name, serAttrs[1].attrName.c_str());
    }
    if (dataFkInfo.attrCount >= 3){
        strcpy(dataFkInfo.masAttr3Name, masAttrs[2].attrName.c_str());
        strcpy(dataFkInfo.serAttr3Name, serAttrs[2].attrName.c_str());
    }
    RecordID recordID;
    fileHandle->insertRecord((BufType)&dataFkInfo);
    recordManager->closeFile();

    dbHandle.refreshHandle();
    return RETVAL_OK;
}

int SystemManager::dropForeignKey(const char *relName, const char *fkName){
    if (!hasRelation(relName)){
        cerr << "[ERROR] Relation <" << relName << "> does not exist." << endl;
        return RETVAL_ERR;
    }
    for (int i = 0, limi = dbHandle.foreignKeys.size(); i < limi; ++i){
        auto &t = dbHandle.foreignKeys[i];
        auto &rid = dbHandle.foreignKeyRecordIDs[i];
        if (strcmp(relName, t.serRelName) == 0 && strcmp(fkName, t.fkName) == 0){
            FileHandler* fileHandle = recordManager->openFile(kDefaultFkCatName);
            RETURNIF(fileHandle->deleteRecord(rid));
            recordManager->closeFile();
            dbHandle.refreshHandle();
            return RETVAL_OK;
        }
    }
    cerr << "[ERROR] Foreign key not found." << endl;
    return RETVAL_ERR;
}

int SystemManager::getForeignKeyList(vector<DataFkInfo> &flist){
    flist.clear();
    for (const auto &t: dbHandle.foreignKeys)
        flist.push_back(t);
    return RETVAL_OK;
}

int SystemManager::getAttributeInfo(const char *relName, const char *attrName, DataAttrInfo &info){
    if (!hasRelation(relName))
        return RETVAL_ERR;
    if (!hasAttribute(relName, attrName))
        return RETVAL_ERR;
    for (const auto &t: dbHandle.attributes)
        if (strcmp(t.attrName, attrName) == 0 && strcmp(t.relName, relName) == 0){
            info = t;
            return RETVAL_OK;
        }
    return RETVAL_NOREC;
}

bool SystemManager::existsRecord(const char *relName, std::vector<AttributeTree::AttributeDescriptor> attrs, std::vector<AttrValue> vals){
    vector<string> rels;
    rels.push_back(string(relName));
    vector<ComparisonTree::ComparisonDescriptor> coms;
    if (attrs.size() != vals.size())
        return false;
    for (int i = 0, limi = attrs.size(); i < limi; ++i)
        coms.push_back(ComparisonTree::ComparisonDescriptor{attrs[i], CmpOP::T_EQ, vals[i], attrs[i], false});

    int rc = RETVAL_OK;
    vector<RecordDescriptor> records = select(attrs, rels, coms, rc);
    if (rc != RETVAL_OK)
        return false;
    return !records.empty();
}


int SystemManager::AddAttr(std::string relName, AttrInfo attr){
    if (!hasRelation(relName.c_str())){
        cerr << "[ERROR] No such table." << endl;
        return RETVAL_ERR;
    }
    if (attr.notNull && !attr.isDefault){
        cerr << "[ERROR] New attribute will be filled with default value or NULL. But this attribute is NOT NULL and no default value is provided." << endl;
        return RETVAL_ERR;
    }
    if (attr.notNull && attr.isDefault && attr.defaultVal.isNull){
        cerr << "[ERROR] Default value is NULL but attribute cannot be NULL." << endl;
        return RETVAL_ERR;
    }
    int attrCount;
    DataAttrInfo *dataAttrInfo;
    RETURNIF(fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo));
    int rc;
    auto records = retrieveRecords(relName, rc);

    vector<pair<string, string>> indexes;
    for (const auto &idx: dbHandle.indexes)
        if (strcmp(idx.relName, relName.c_str()) == 0)
            indexes.push_back(make_pair(string(idx.idxName), string(idx.attrName)));

    
    dropTable(relName.c_str(), false);
    AttrInfo *attrInfo = new AttrInfo[attrCount + 1];
    for (int i = 0; i < attrCount; ++i){
        strcpy(attrInfo[i].attrName, dataAttrInfo[i].attrName);
        attrInfo[i].attrLength = dataAttrInfo[i].attrLength;
        attrInfo[i].attrType = dataAttrInfo[i].attrType;
        attrInfo[i].isPrimaryKey = dataAttrInfo[i].isPrimaryKey;
        attrInfo[i].notNull = dataAttrInfo[i].notNull;
        attrInfo[i].isDefault = dataAttrInfo[i].isDefault;
        if (attrInfo[i].isDefault){
            if (attrInfo[i].defaultVal.isNull)
                *((unsigned int*)dataAttrInfo[i].defaultVal) = NULL_MAGIC_NUMBER;  
            else
                switch (attrInfo[i].attrType){
                    case T_INT:
                        memcpy((void*)dataAttrInfo[i].defaultVal, (void*)&attrInfo[i].defaultVal.i, sizeof (int));
                        break;
                    case T_FLOAT:
                        memcpy((void*)dataAttrInfo[i].defaultVal, (void*)&attrInfo[i].defaultVal.f, sizeof (float));
                        break;
                    case T_STRING:
                        strcpy(dataAttrInfo[i].defaultVal, attrInfo[i].defaultVal.s.c_str());
                        break;
                    case T_DATE:
                        strcpy(dataAttrInfo[i].defaultVal, attrInfo[i].defaultVal.s.c_str());
                        break;
                }
        }
    }
    attrInfo[attrCount] = attr;
    createTable(relName.c_str(), attrCount + 1, attrInfo);

    for (const auto &idxp: indexes)
        createIndex(relName, (SystemManager::Attribute)(relName, idxp.second), idxp.first);

    for (auto record: records){
        if (!attr.isDefault)
            record.second.attrVals.push_back(AttrValue{attr.attrType, 0, 0.0, string(), true});
        else
            record.second.attrVals.push_back(attr.defaultVal);
        Insert(relName, NULL, record.second.attrVals, false);
    }
    delete[] attrInfo;
    return RETVAL_OK;
}

int SystemManager::DelAttr(std::string relName, std::string attrName){
    if (!hasRelation(relName.c_str())){
        cerr << "[ERROR] No such table." << endl;
        return RETVAL_ERR;
    }
    if (!hasAttribute(relName.c_str(), attrName.c_str())){
        cerr << "[ERROR] No such attribute in table <" << relName << ">." << endl;
        return RETVAL_ERR;
    }
    
    for (const auto &pk: dbHandle.attributes)
        if (relName == string(pk.relName) && attrName == string(pk.attrName))
            if (pk.isPrimaryKey){
                cerr << "[ERROR] Cannot delete an attribute which is a part of primary key." << endl;
                return RETVAL_ERR;
            }
    
    for (const auto &fk: dbHandle.foreignKeys)
        if (string(fk.serRelName) == relName)
            if (string(fk.serAttr1Name) == attrName || 
                string(fk.serAttr2Name) == attrName || 
                string(fk.serAttr3Name) == attrName){
                    cerr << "[ERROR] Cannot delete an attribute which is a part of a certain foreign key." << endl;
                    return RETVAL_ERR;
                }

    int attrCount;
    DataAttrInfo *dataAttrInfo;
    RETURNIF(fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo));
    int rc;
    auto records = retrieveRecords(relName, rc);

    vector<pair<string, string>> indexes;
    for (const auto &idx: dbHandle.indexes)
        if (strcmp(idx.relName, relName.c_str()) == 0)
            indexes.push_back(make_pair(string(idx.idxName), string(idx.attrName)));

    
    dropTable(relName.c_str(), false);
    AttrInfo *attrInfo = new AttrInfo[attrCount];
    int delIndex = -1;
    for (int i = 0; i < attrCount; ++i){
        strcpy(attrInfo[i].attrName, dataAttrInfo[i].attrName);
        attrInfo[i].attrLength = dataAttrInfo[i].attrLength;
        attrInfo[i].attrType = dataAttrInfo[i].attrType;
        attrInfo[i].isPrimaryKey = dataAttrInfo[i].isPrimaryKey;
        attrInfo[i].notNull = dataAttrInfo[i].notNull;
        attrInfo[i].isDefault = dataAttrInfo[i].isDefault;
        if (attrInfo[i].isDefault){
            if (attrInfo[i].defaultVal.isNull)
                *((unsigned int*)dataAttrInfo[i].defaultVal) = NULL_MAGIC_NUMBER;  
            else
                switch (attrInfo[i].attrType){
                    case T_INT:
                        memcpy((void*)dataAttrInfo[i].defaultVal, (void*)&attrInfo[i].defaultVal.i, sizeof (int));
                        break;
                    case T_FLOAT:
                        memcpy((void*)dataAttrInfo[i].defaultVal, (void*)&attrInfo[i].defaultVal.f, sizeof (float));
                        break;
                    case T_STRING:
                        strcpy(dataAttrInfo[i].defaultVal, attrInfo[i].defaultVal.s.c_str());
                        break;
                    case T_DATE:
                        strcpy(dataAttrInfo[i].defaultVal, attrInfo[i].defaultVal.s.c_str());
                        break;
                }
        }
        if (strcmp(attrInfo[i].attrName, attrName.c_str()) == 0)
            delIndex = i;
    }
    if (delIndex == -1){
        cerr << "[ERROR] Inner error in DelAttr()." << endl;
        return RETVAL_ERR;
    }
    for (int i = delIndex + 1; i < attrCount; ++i)  
        attrInfo[i-1] = attrInfo[i];
    createTable(relName.c_str(), attrCount - 1, attrInfo);

    for (const auto &idxp: indexes)
        if (idxp.second != attrName)
            createIndex(relName, SystemManager::Attribute{relName, idxp.second}, idxp.first);

    for (auto record: records){
        record.second.attrVals.erase(record.second.attrVals.begin() + delIndex);
        Insert(relName, NULL, record.second.attrVals, false);
    }
    delete[] attrInfo;
    return RETVAL_OK;
}

int SystemManager::ModifyAttr(std::string relName, std::string attrName, AttrInfo attr){
    RETURNIF(DelAttr(relName, attrName));
    RETURNIF(AddAttr(relName, attr));
}

int SystemManager::RenameTable(std::string a, std::string b){
    if (!hasRelation(a.c_str())){
        cerr << "[ERROR] No such table." << endl;
        return RETVAL_ERR;
    }
    if (a == kDefaultRelCatName || a == kDefaultFkCatName || a == kDefaultIdxCatName || a == kDefaultAttrCatName){
        cerr << "[ERROR] You cannot modify system table." << endl;
        return RETVAL_ERR;
    }
    if (hasRelation(b.c_str())){
        cerr << "[ERROR] Table <" << b << "> already exists." << endl;
        return RETVAL_ERR;
    }
    RETURNIF(GlobalFileHandler::instance()->renameFile(a.c_str(), b.c_str()));

    
    for (const auto &idx: dbHandle.indexes)
        if (string(idx.relName) == a){
            string attrName = idx.attrName;
            for (const auto &attr: dbHandle.attributes)
                if (string(attr.attrName) == attrName){
                    string indexNo = to_string(attr.indexNo);
                    string o = a + "_idx_" + indexNo;
                    string n = b + "_idx_" + indexNo;
                    RETURNIF(GlobalFileHandler::instance()->renameFile(o.c_str(), n.c_str()));
                    break;
                }
        }
    
    
    for (int i = 0, limi = dbHandle.relationRecordIDs.size(); i < limi; ++i)
        if (strcmp(dbHandle.relations[i].relName, a.c_str()) == 0){
            DataRelInfo relData = dbHandle.relations[i];
            RecordID relDataRID = dbHandle.relationRecordIDs[i];
            strcpy(relData.relName, b.c_str());
            FileHandler *fileHandle = recordManager->openFile(kDefaultRelCatName);
            fileHandle->modifyRecord(relDataRID, (BufType)(&relData));
            recordManager->closeFile();
        }
    dbHandle.refreshHandle();

    for (int i = 0, limi = dbHandle.attributes.size(); i < limi; ++i)
        if (strcmp(dbHandle.attributes[i].relName, a.c_str()) == 0){
            DataAttrInfo attrData = dbHandle.attributes[i];
            RecordID attrDataRID = dbHandle.attributeRecordIDs[i];
            strcpy(attrData.relName, b.c_str());
            FileHandler *fileHandle = recordManager->openFile(kDefaultAttrCatName);
			fileHandle->modifyRecord(attrDataRID, (BufType)(&attrData));
			recordManager->closeFile();
        }

    for (int i = 0, limi = dbHandle.indexes.size(); i < limi; ++i)
        if (strcmp(dbHandle.indexes[i].relName, a.c_str()) == 0){
            DataIdxInfo idxData = dbHandle.indexes[i];
            RecordID idxDataRID = dbHandle.indexRecordIDs[i];
            strcpy(idxData.relName, b.c_str());
            FileHandler *fileHandle = recordManager->openFile(kDefaultIdxCatName);
			fileHandle->modifyRecord(idxDataRID, (BufType)(&idxData));
			recordManager->closeFile();
        }

    for (int i = 0, limi = dbHandle.foreignKeys.size(); i < limi; ++i){
        if (strcmp(dbHandle.foreignKeys[i].masRelName, a.c_str()) == 0){
            DataFkInfo fkData = dbHandle.foreignKeys[i];
            RecordID fkDataRID = dbHandle.foreignKeyRecordIDs[i];
            strcpy(fkData.masRelName, b.c_str());
            FileHandler *fileHandle = recordManager->openFile(kDefaultFkCatName);
			fileHandle->modifyRecord(fkDataRID, (BufType)(&fkData));
			recordManager->closeFile();
        }
        if (strcmp(dbHandle.foreignKeys[i].serRelName, a.c_str()) == 0){
            DataFkInfo fkData = dbHandle.foreignKeys[i];
            RecordID fkDataRID = dbHandle.foreignKeyRecordIDs[i];
            strcpy(fkData.serRelName, b.c_str());
            FileHandler *fileHandle = recordManager->openFile(kDefaultFkCatName);
			fileHandle->modifyRecord(fkDataRID, (BufType)(&fkData));
			recordManager->closeFile();
        }
    }

    dbHandle.refreshHandle();
    return RETVAL_OK;
}

int SystemManager::ShowDatabase(){
    dirent *dirp;
    DIR* dir = opendir("./");
    while ((dirp = readdir(dir)) != nullptr)
        if (dirp->d_type == DT_DIR)
            if (strcmp(dirp->d_name, "CMakeFiles") != 0 &&
                strcmp(dirp->d_name, ".") != 0 &&
                strcmp(dirp->d_name, "..") != 0)
                cout << "[Database]\t" << dirp->d_name << endl;
    return RETVAL_OK;
}