#ifndef DATABASE_SYSTEMMANAGER_H
#define DATABASE_SYSTEMMANAGER_H


#include <map>
#include "GlobalFileHandler.h"
#include "DBHandle.h"


class SystemManager {
public:

    static SystemManager* instance();
    static void resetInstance();

    
    int createDB(const char* dbName);
    int dropDB(const char* dbName);
    int openDB(const char *dbName);
    int closeDB();

    
    int createTable(const char *relName, int attrCount, AttrInfo *attributes);
    
    int dropTable(const char *relName, bool check = true);
    int createIndex(std::string relName, AttributeTree::AttributeDescriptor attr, std::string idxName);
    int dropIndex(std::string relName, std::string idxName);

    int addPrimaryKey(const char *relName, std::vector<std::string> attrs);
    int dropPrimaryKey(const char *relName);
    int getPrimaryKeyList(const char *relName, std::vector<std::string> &plist);

    int addForeignKey(const char *fkName, const char *serRelName, const char *masRelName, 
            std::vector<AttributeTree::AttributeDescriptor> &serAttrs, std::vector<AttributeTree::AttributeDescriptor> &masAttrs, bool checked = false);
    int getForeignKeyList(std::vector<DataFkInfo> &flist);
    int dropForeignKey(const char *relName, const char *fkName);

    
    int getAttributeInfo(const char *relName, const char *attrName, DataAttrInfo &info);

    
    bool existsRecord(const char *relName, std::vector<AttributeTree::AttributeDescriptor> attrs, std::vector<AttrValue> vals);

    int load(const char *relName, const char *fileName);
    int help();
    std::vector<std::vector<string> > qHelp();
    int help(const char *relName);
    std::vector<std::vector<std::string>> qHelp(const char* relName);
    int print(const char *relName) {return dbHandle.print(relName);}
    std::map<RecordID, RecordDescriptor> qPrint(const char* relName) {return dbHandle.qPrint(relName);}
    int qUpdate(const std::string& relName, const RecordID& recordID,
            int attrNo, const AttrValue& newVal);
    int set(const char *paramName, const char *value);

    
    int Select(std::vector<AttributeTree::AttributeDescriptor> attrs,
            std::vector<std::string> rels,
            std::vector<ComparisonTree::ComparisonDescriptor> coms);

    
    int Insert(std::string relName, std::vector<std::string>* attrs,
            std::vector<AttrValue> vals, bool check = true);

    
    int Update(std::string relName,
            AttributeTree::AttributeDescriptor attr,
            AttrValue val,
            std::vector<ComparisonTree::ComparisonDescriptor> coms);


    int Delete(std::string relName,
            std::vector<ComparisonTree::ComparisonDescriptor> coms);

    
    
    int fillAttributesFromTable(const char* relName, int& attrCount, DataAttrInfo*& dataAttrInfo)
    {RETURNIF(dbHandle.fillAttributesFromTable(relName, attrCount, dataAttrInfo)); return RETVAL_OK;}

    std::vector<RecordDescriptor> select(std::vector<AttributeTree::AttributeDescriptor> attrs,
                                        std::vector<std::string> rels,
                                        std::vector<ComparisonTree::ComparisonDescriptor> coms,
                                        int& rc);

    int AddAttr(std::string relName, AttrInfo attr);
    int DelAttr(std::string relName, std::string attrName);
    int ModifyAttr(std::string relName, std::string attrName, AttrInfo attr);
    int RenameTable(std::string a, std::string b);

    int ShowDatabase();

    ~SystemManager();
private:
    SystemManager();

    static SystemManager* systemManager;
    GlobalFileHandler* recordManager;
    DBHandle dbHandle;
    bool hasOpenDB;
    char currentDBName[MAX_NAME];

    
    bool hasRelation(const char *relName) {return dbHandle.hasRelation(relName);}

    
    
    bool hasAttribute(const char *relName, const char *attrName) {return dbHandle.hasAttribute(relName, attrName);}
    bool hasIndex(const char *relName, const char *idxName) {return dbHandle.hasIndex(relName, idxName);}

    typedef ComparisonTree::ComparisonDescriptor Comparison;
    typedef AttributeTree::AttributeDescriptor Attribute;

    std::map<RecordID, RecordDescriptor> retrieveRecords(std::string relName, int& rc)
    { return dbHandle.retrieveRecords(relName, rc);}

    bool checkRelations(const std::vector<std::string> &relations);
    bool checkAttributes(std::vector<Attribute> &attributes, std::vector<std::string> &relations);
    bool checkComparison(std::vector<Comparison> &coms, std::string &relation);
    bool checkComparisons(std::vector<Comparison> &coms, std::vector<std::string> &relations);

    bool isValid(std::vector<Comparison> &coms, RecordDescriptor &record, const std::string &relation);

    void iterateCrossProduct(std::vector<std::vector<RecordDescriptor>> &records,
                            std::vector<AttributeTree::AttributeDescriptor> attrs,
                            std::vector<std::string> &rels,
                            std::vector<Comparison> &coms,
                            int depth,
                            std::vector<RecordDescriptor>& output);

    std::vector<RecordDescriptor> retrieveRecordsByIndex(std::string relName, const std::vector<Comparison>& coms, int& rc);

    static vector<string> &split(const string &s, char delim, vector<string> &elems) {
        stringstream ss(s);
        string item;
        while (getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }


    static vector<std::string> split(const string &s, char delim) {
        vector<string> elems;
        split(s, delim, elems);
        return elems;
    }
};


bool operator < (const vector<AttrValue> &a, const vector<AttrValue> &b);
bool operator == (const vector<AttrValue> &a, const vector<AttrValue> &b);

#endif 
