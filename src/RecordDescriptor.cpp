#include <string.h>
#include "RecordDescriptor.h"
#include "SystemManager.h"
using namespace std;

RecordDescriptor::RecordDescriptor() {

}


AttrValue &RecordDescriptor::operator[](const string &attrName) {
    int i = getIndex(attrName);
    return attrVals[i];
}

void RecordDescriptor::assign(const string &attrName, AttrValue &val) {
    int i = getIndex(attrName);
    attrVals[i] = val;
}

bool RecordDescriptor::checkAssignType(const string &attrName, AttrValue &val) {
    const AttrValue& constValue = attrVals[getIndex(attrName)];
    if(constValue.type == val.type)
        return true;
    if(constValue.type == T_FLOAT && val.type == T_INT)
        return true;
    return false;
}

bool RecordDescriptor::checkCompareType(const string &attrName, AttrValue &val) {
    const AttrValue& constValue = attrVals[getIndex(attrName)];
    if(constValue.type == val.type)
        return true;
    if((constValue.type == T_INT && val.type == T_FLOAT) ||
            (constValue.type == T_FLOAT && val.type == T_INT))
        return true;
    return false;
}

int RecordDescriptor::toRecord(const RecordID rid, Record& record) {
    int recordSize = 0;
    int attrCount = 0;
    DataAttrInfo* dataAttrInfo = nullptr;
    SystemManager::instance()->fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo);
    int nullVectorBase = dataAttrInfo[attrCount-1].offset + dataAttrInfo[attrCount-1].attrLength;
    recordSize = nullVectorBase + attrCount;
    if(attrNames.size() != attrCount) {
        cerr << "[ERROR] InValid RecordDescriptor!" << endl;
        return RETVAL_ERR;
    }
    char* buffer = new char[recordSize];
    for(int i = 0; i < attrCount; ++i) {
        int offset = dataAttrInfo[i].offset;
        if(attrVals[i].type == T_INT) {
            memcpy(buffer + offset, (void*)&(attrVals[i].i), sizeof(int));
        }
        else if(attrVals[i].type == T_FLOAT) {
            memcpy(buffer + offset, (void*)&(attrVals[i].f), 4);
        }
        else
        {
            if(attrVals[i].s.size() < dataAttrInfo[i].attrLength) {
                strncpy(buffer + offset, attrVals[i].s.c_str(), dataAttrInfo[i].attrLength);
            }
            else {
                memcpy(buffer + offset, attrVals[i].s.c_str(), dataAttrInfo[i].attrLength);
            }
        }
    }
    for(int i = 0; i < attrCount; ++i) {
        if(attrVals[i].isNull) {
            memset(buffer + nullVectorBase + i, 1, 1);
        }
        else {
            memset(buffer + nullVectorBase + i, 0, 1);
        }
    }
    record.assign(Record((uint*)buffer, recordSize, rid));
    delete [] dataAttrInfo;
    delete [] buffer;
    return RETVAL_OK ;
}


int RecordDescriptor::getIndex(string attrName) {
    int i = 0;
    for(; i < attrNames.size(); ++i) {
        if(attrNames[i] == attrName)
            break;
    }
    return i;
}

RecordDescriptor RecordDescriptor::createRecordDescriptor(const std::string &relName,
                                                          vector<AttrValue> vals, int &rc) {
    RecordDescriptor recordDescriptor;
    recordDescriptor.relName = relName;
    int attrCount = 0;
    DataAttrInfo* dataAttrInfo = nullptr;
    SystemManager::instance()->fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo);
    if(attrCount != vals.size()) {
        cerr << "[ERROR] Relation <" << relName << "> has " << attrCount << " attributes, but you only provided " << vals.size() << "." << endl;
        rc = RETVAL_ERR;
        return recordDescriptor;
    }
    AttrValue primaryValue;
    DataAttrInfo primaryAttrInfo;
    bool hasPrimaryKey = false;
    for(int i = 0; i < attrCount; ++i) {
        if(vals[i].isNull) {
            if(dataAttrInfo[i].notNull) {
                
                cerr << "[ERROR] Insert NULL into NOT NULL attribute." << endl;
                rc = RETVAL_ERR;
                delete[] dataAttrInfo;
                return recordDescriptor;
            }
            else {
                recordDescriptor.attrNames.push_back(dataAttrInfo[i].attrName);
                vals[i].type = dataAttrInfo[i].attrType;
                recordDescriptor.attrVals.push_back(vals[i]);
            }
        }
        else if((dataAttrInfo[i].attrType == vals[i].type)
           || (dataAttrInfo[i].attrType == T_FLOAT && vals[i].type == T_INT)) {
            if(dataAttrInfo[i].isPrimaryKey) {
                
                hasPrimaryKey = true;
                primaryValue = vals[i];
                primaryAttrInfo = dataAttrInfo[i];
            }

            recordDescriptor.attrNames.push_back(dataAttrInfo[i].attrName);
            recordDescriptor.attrVals.push_back(vals[i]);
        }
        else {
            cerr << "[ERROR] Input type is invalid." << endl;
            rc = RETVAL_ERR;
            delete[] dataAttrInfo;
            return recordDescriptor;
        }
    }

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    rc = RETVAL_OK;
    delete[] dataAttrInfo;
    return recordDescriptor;
}

RecordDescriptor RecordDescriptor::createRecordDescriptor(const std::string &relName,
                                                        vector<std::string> &attrs,
                                                        vector<AttrValue> vals, int &rc) {
    RecordDescriptor recordDescriptor;
    if (attrs.size() != vals.size()){
        cerr << "[ERROR] The length of insert attrs should equal to the length of insert vals." << endl;
        rc = RETVAL_ERR;
        return recordDescriptor;
    }
    recordDescriptor.relName = relName;
    int attrCount = 0;
    DataAttrInfo* dataAttrInfo = nullptr;
    SystemManager::instance()->fillAttributesFromTable(relName.c_str(), attrCount, dataAttrInfo);

    int givenAttrCount = attrs.size();

    
    for (int j = 0; j < givenAttrCount; ++j){
        int idx = -1;
        for (int i = 0; i < attrCount; ++i)
            if (strcmp(dataAttrInfo[i].attrName, attrs[j].c_str()) == 0){
                idx = j;
                break;
            }
        if (idx == -1){
            rc = RETVAL_ERR;
            cerr << "[ERROR] Attribute <" << attrs[j] << "> not found in relation." << endl;
            delete[] dataAttrInfo;
            return recordDescriptor;
        }
    }

    for(int i = 0; i < attrCount; ++i) {    
        int idx = -1;
        for (int j = 0; j < givenAttrCount; ++j)    
            if (strcmp(dataAttrInfo[i].attrName, attrs[j].c_str()) == 0){
                idx = j;
                break;
            }
        if (idx == -1){ 
            if (!dataAttrInfo[i].isDefault){    
                if (dataAttrInfo[i].notNull){   
                    rc = RETVAL_ERR;
                    cerr << "[ERROR] Attribute <" << dataAttrInfo[i].attrName << "> has no default value and cannot be NULL, but you leave it blank." << endl;
                    delete[] dataAttrInfo;
                    return recordDescriptor;
                }else{  
                    AttrValue val;
                    val.isNull = true;
                    val.type = dataAttrInfo[i].attrType;
                    recordDescriptor.attrNames.push_back(dataAttrInfo[i].attrName);
                    recordDescriptor.attrVals.push_back(val);
                }
            }else{  
                AttrValue val;
                val.type = dataAttrInfo[i].attrType;
                unsigned int magic = *((unsigned int*)dataAttrInfo[i].defaultVal);
                if (magic == NULL_MAGIC_NUMBER)
                    val.isNull = true;
                else{
                    switch (val.type) {
                        case T_INT:
                            val.i = *((int*)dataAttrInfo[i].defaultVal);
                            break;
                        case T_FLOAT:
                            val.f = *((float*)dataAttrInfo[i].defaultVal);
                            break;
                        case T_STRING:
                            val.s = std::string(dataAttrInfo[i].defaultVal);
                            break;
                        case T_DATE:
                            val.s = std::string(dataAttrInfo[i].defaultVal);
                            break;
                    }
                    val.isNull = false;
                }

                recordDescriptor.attrNames.push_back(dataAttrInfo[i].attrName);
                recordDescriptor.attrVals.push_back(val);
            }
        }else{  
            if(vals[idx].isNull) {
                if(dataAttrInfo[i].notNull) {
                    
                    cerr << "[ERROR] Insert NULL into NOT NULL attribute!" << endl;
                    rc = RETVAL_ERR;
                    delete[] dataAttrInfo;
                    return recordDescriptor;
                }
                else {
                    recordDescriptor.attrNames.push_back(dataAttrInfo[i].attrName);
                    vals[idx].type = dataAttrInfo[i].attrType;
                    recordDescriptor.attrVals.push_back(vals[idx]);
                }
            }
            else if((dataAttrInfo[i].attrType == vals[idx].type)
            || (dataAttrInfo[i].attrType == T_FLOAT && vals[idx].type == T_INT)) {
                recordDescriptor.attrNames.push_back(dataAttrInfo[i].attrName);
                recordDescriptor.attrVals.push_back(vals[idx]);
            }
            else {
                cerr << "[ERROR] Input type is invalid." << endl;
                rc = RETVAL_ERR;
                delete[] dataAttrInfo;
                return recordDescriptor;
            }
        }
    }
    rc = RETVAL_OK;
    delete[] dataAttrInfo;
    return recordDescriptor;
}


RecordDescriptor RecordDescriptor::filteredByAttributeName(std::vector<AttributeTree::AttributeDescriptor> attrs, bool checkRel) const{
    RecordDescriptor recordDescriptor;
    recordDescriptor.relName = relName;
    
    for (const auto &attr : attrs) {
        for (int i = 0; i < attrNames.size(); ++i) {
            if (checkRel)
                if (attr.relName != relName)
                    continue;
            if(attrNames[i] == attr.attrName) {
                recordDescriptor.attrNames.push_back(attr.attrName);
                recordDescriptor.attrVals.push_back(attrVals[i]);
            }
        }
    }
    return recordDescriptor;
}


RecordDescriptor RecordDescriptor::concatenate(const RecordDescriptor &next) const{
    RecordDescriptor recordDescriptor;
    for(const auto& attr : attrVals)
        recordDescriptor.attrVals.push_back(attr);
    for(const auto& attr : next.attrVals)
        recordDescriptor.attrVals.push_back(attr);
    return recordDescriptor;
}
