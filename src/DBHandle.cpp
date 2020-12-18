#include <string.h>
#include <set>
#include <map>
#include "DBHandle.h"
#include "GlobalFileHandler.hpp"
#include "FileScan.hpp"
#include "Printer.hpp"
#include "SystemManager.h"

using namespace std;

DBHandle::DBHandle() {

}



int DBHandle::refreshHandle() {
    relations.clear();
    attributes.clear();
    foreignKeys.clear();
    indexes.clear();
    relationRecordIDs.clear();
    attributeRecordIDs.clear();
    foreignKeyRecordIDs.clear();
    indexRecordIDs.clear();
    GlobalFileHandler *recordManager = GlobalFileHandler::instance();
    FileHandler* fileHandle = recordManager->openFile(kDefaultRelCatName);
    FileScan fileScan;
    RETURNIF(fileScan.openScan(*fileHandle, AttrType::T_INT, sizeof(int), 0, CmpOP::T_NO, nullptr));
    Record record;
    int rc = RETVAL_OK;
    while(rc != RETVAL_EOF) {
        rc = fileScan.getNextRec(record);
        if(rc == RETVAL_ERR) {
            return rc;
        }
        if(rc == RETVAL_EOF) {
            break;
        }
        DataRelInfo* dataRelInfo = (DataRelInfo *) record.getData();
        relations.push_back(*dataRelInfo);
        relationRecordIDs.push_back(record.getRecordID());
    }
    RETURNIF(fileScan.closeScan());

    fileHandle = recordManager->openFile(kDefaultAttrCatName);
    RETURNIF(fileScan.openScan(*fileHandle, AttrType::T_INT, sizeof(int), 0, CmpOP::T_NO, nullptr));
    rc = RETVAL_OK;
    while(rc != RETVAL_EOF) {
        rc = fileScan.getNextRec(record);
        if(rc == RETVAL_ERR) {
            return rc;
        }
        if(rc == RETVAL_EOF) {
            break;
        }
        DataAttrInfo* dataAttrInfo = (DataAttrInfo*) record.getData();
        attributes.push_back(*dataAttrInfo);
        attributeRecordIDs.push_back(record.getRecordID());
    }
    RETURNIF(fileScan.closeScan());

    fileHandle = recordManager->openFile(kDefaultFkCatName);
    RETURNIF(fileScan.openScan(*fileHandle, AttrType::T_INT, sizeof(int), 0, CmpOP::T_NO, nullptr));
    rc = RETVAL_OK;
    while (rc != RETVAL_EOF) {
        rc = fileScan.getNextRec(record);
        if(rc == RETVAL_ERR) {
            return rc;
        }
        if(rc == RETVAL_EOF) {
            break;
        }
        DataFkInfo* dataFkInfo = (DataFkInfo*) record.getData();
        foreignKeys.push_back(*dataFkInfo);
        foreignKeyRecordIDs.push_back(record.getRecordID());
    }
    RETURNIF(fileScan.closeScan());

    fileHandle = recordManager->openFile(kDefaultIdxCatName);
    RETURNIF(fileScan.openScan(*fileHandle, AttrType::T_INT, sizeof(int), 0, CmpOP::T_NO, nullptr));
    rc = RETVAL_OK;
    while (rc != RETVAL_EOF) {
        rc = fileScan.getNextRec(record);
        if(rc == RETVAL_ERR) {
            return rc;
        }
        if(rc == RETVAL_EOF) {
            break;
        }
        DataIdxInfo* dataIdxInfo = (DataIdxInfo*) record.getData();
        indexes.push_back(*dataIdxInfo);
        indexRecordIDs.push_back(record.getRecordID());
    }
    RETURNIF(fileScan.closeScan());

    return RETVAL_OK;
}

/*
    创建一个数据表table，其参数如下：
    relName:    表名
    attrCount:  列数
    attributes: 列信息
    其中，列信息是AttrInfo类型
*/
int DBHandle::createTable(const char *relName, int attrCount, AttrInfo *attributes) {
    vector<string> primary_key;

    
    return RETVAL_OK;
}

int DBHandle::dropTable(const char *relName) {
    GlobalFileHandler* recordManager = GlobalFileHandler::instance();
    
    int rc = RETVAL_OK;
    bool found = false;
    int i = 0;
    for(; i < relations.size(); ++i) {
        if(strcmp(relations[i].relName, relName) == 0) {
            found = true;
            break;
        }
    }
    if(!found)
    {
        cerr << "[ERROR] No such table." << endl;
        return RETVAL_ERR;
    }

    RecordID recordID = relationRecordIDs[i];
    FileHandler* fileHandle = recordManager->openFile(kDefaultRelCatName);
    RETURNIF(fileHandle->deleteRecord(recordID));
    RETURNIF(recordManager->destroyFile(relName));

    
    fileHandle = recordManager->openFile(kDefaultAttrCatName);
    for(i = 0; i < attributes.size(); ++i) {
        if(strcmp(attributes[i].relName, relName) == 0) {
            RETURNIF(fileHandle->deleteRecord(attributeRecordIDs[i]));
        }
    }
    refreshHandle();
    return 0;
}

int DBHandle::createIndex(const char *relName, const char *attrName) {
    return 0;
}

int DBHandle::dropIndex(const char *relName, const char *attrName) {
    return 0;
}

int DBHandle::help() {
    int rc = RETVAL_OK;
    auto records = retrieveRecords(kDefaultRelCatName, rc);
    RETURNIF(rc);
    vector<RecordDescriptor> descriptors;
    for(auto it = records.begin(); it != records.end(); ++it)
        descriptors.push_back(it->second);
    Printer::printAll(descriptors);
    return 0;































    
}

vector<vector<string>> DBHandle::qHelp()
{
    int rc = RETVAL_OK;
    auto records = retrieveRecords(kDefaultRelCatName, rc);
    vector<vector<string>> ret;
    for(auto it = records.begin(); it != records.end(); ++it) {
        vector<string> tmp;
        tmp.push_back(it->second["relName"].s);
        tmp.push_back(to_string(it->second["recordSize"].i));
        tmp.push_back(to_string(it->second["attrCount"].i));
        tmp.push_back(to_string(it->second["indexCount"].i));
        ret.push_back(tmp);
    }
    return ret;
}

int DBHandle::help(const char *relName) {
    int rc = RETVAL_OK;
    auto records = retrieveRecords(kDefaultAttrCatName, rc);
    RETURNIF(rc);
    vector<RecordDescriptor> descriptors;
    for(auto it = records.begin(); it != records.end(); ++it) {
        if(it->second["relName"].s == string(relName))
            descriptors.push_back(it->second);
    }
    if(descriptors.empty()) {
        cerr << "[ERROR] No Such Relation: '" << relName << "'!" << endl;
        return 0;
    }
    Printer::printAll(descriptors);
    return 0;






































    
}

std::vector<std::vector<string> > DBHandle::qHelp(const char *relName)
{
    int rc = RETVAL_OK;
    auto records = retrieveRecords(kDefaultAttrCatName, rc);
    vector<vector<string>> ret;
    for(auto it = records.begin(); it != records.end(); ++it) {
        if(it->second["relName"].s == string(relName)) {
            vector<string> tmp;
            tmp.push_back(it->second["attrName"].s);
            tmp.push_back(to_string(it->second["attrType"].i));
            tmp.push_back(to_string(it->second["attrLength"].i));
            tmp.push_back(to_string(it->second["offset"].i));
            tmp.push_back(to_string(it->second["indexNo"].i));
            tmp.push_back(to_string(it->second["isPrimaryKey"].i));
            tmp.push_back(to_string(it->second["notNull"].i));
            ret.push_back(tmp);
        }
    }
    return ret;
}

int DBHandle::print(const char *relName) {
    int rc = RETVAL_OK;
    auto records = retrieveRecords(relName, rc);
    RETURNIF(rc);
    vector<RecordDescriptor> descriptors;
    for(auto it = records.begin(); it != records.end(); ++it)
        descriptors.push_back(it->second);
    Printer::printAll(descriptors);
    return 0;
}

map<RecordID, RecordDescriptor> DBHandle::qPrint(const char *relName)
{
    int rc = RETVAL_OK;
    return retrieveRecords(relName, rc);
}


DBHandle::~DBHandle() {

}

/**
 * Remember to delete the DataAttrInfo Array after calling this function
 * 在dataAttrInfo 中填入relName的表中的Attr项
 */
int DBHandle::fillAttributesFromTable(const char *relName, int &attrCount, DataAttrInfo *&dataAttrInfo) {
    int i = 0;
    for(; i < relations.size(); ++i) {
        if(strcmp(relations[i].relName, relName) == 0) {
            break;
        }
    }
    if(i == relations.size()) {
        cerr << "[ERROR] No Such Table" << endl;
        return RETVAL_ERR;
    }
    attrCount = relations[i].attrCount;
    dataAttrInfo = new DataAttrInfo[attrCount];
    
    
    int j = 0;
    for(i = 0; i < attributes.size(); ++i) {
        
        if(strcmp(attributes[i].relName, relName) == 0) {
            dataAttrInfo[j++] = attributes[i];
        }
    }
    assert(j == attrCount);
    return RETVAL_OK;
}

bool DBHandle::hasRelation(const char *relName) {
    for(int i = 0; i < relations.size(); ++i) {
        if(strcmp(relations[i].relName, relName) == 0) {
            return true;
        }
    }
    return false;
}

bool DBHandle::hasAttribute(const char *relName, const char *attrName) {
    for(int i = 0; i < attributes.size(); ++i) {
        if(strcmp(attributes[i].attrName, attrName) == 0 && strcmp(attributes[i].relName, relName) == 0) {
            return true;
        }
    }
    return false;
}

map<RecordID, RecordDescriptor> DBHandle::retrieveRecords(string relName, int &rc) {
    map<RecordID, RecordDescriptor> descriptors;

    
    DataAttrInfo* dataAttrInfo;
    int attrCount;
    rc = fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo);
    if(rc != RETVAL_OK) {
        cerr << "[ERROR] Invalid relName" << endl;
        return descriptors;
    }

    
    FileHandler* fileHandle = GlobalFileHandler::instance()->openFile(relName.c_str());
    FileScan fileScan;
    rc = fileScan.openScan(*fileHandle);
    if(rc != RETVAL_OK) {
        cerr << "error" << endl;
        return descriptors;
    }
    
    Record record;
    RecordID recordID;
    const char *pData;
    while(rc == RETVAL_OK) {
        RecordDescriptor recordDescriptor;
        rc = fileScan.getNextRec(record);
        if (rc == RETVAL_EOF) {
            break;
        }
        recordID = record.getRecordID();
        pData = (char*)record.getData();
        
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
        descriptors[recordID] = recordDescriptor;
    }
    rc = RETVAL_OK;
    delete [] dataAttrInfo;
    return descriptors;
}

RecordDescriptor DBHandle::retrieveOneRecord(std::string relName, const RecordID& recordID, int &rc) {
    
    DataAttrInfo* dataAttrInfo;
    int attrCount;
    rc = fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo);
    if(rc != RETVAL_OK) {
        cerr << "[ERROR] Invalid relName" << endl;
        return RecordDescriptor();
    }
    RecordDescriptor recordDescriptor;

    FileHandler* fileHandle = GlobalFileHandler::instance()->openFile(relName.c_str());
    Record record;
    fileHandle->getRecordById(recordID, record);
    const char* pData = (char*)record.getData();
    
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
        if(t == 1)
            recordDescriptor.attrVals[i].isNull = true;
        else
            recordDescriptor.attrVals[i].isNull = false;
    }
    recordDescriptor.relName = relName;
    return recordDescriptor;
}

bool DBHandle::hasIndex(const char *relName, const char *idxName){
    for (int i = 0, lim = indexes.size(); i < lim; ++i)
        if (strcmp(relName, indexes[i].relName) == 0 && strcmp(idxName, indexes[i].idxName) == 0)
            return true;
    return false;
}