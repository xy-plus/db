#ifndef DATABASE_RECORDMANAGER_H
#define DATABASE_RECORDMANAGER_H


#include "../filesystem/bufmanager/BufPageManager.h"
#include "global.h"

#include "FileHandler.hpp"

class GlobalFileHandler {
public:
	static GlobalFileHandler *instance() {
		if (recordManager == nullptr) {
			recordManager = new GlobalFileHandler();
		}
		return recordManager;
	}

	static void resetInstance() {
		delete recordManager;
		recordManager = new GlobalFileHandler();
	}


	~GlobalFileHandler() {
		// When will the singleton be released ?
		// Is it necessary to delete the followings ?
		//bufPageManager->close();
		closeFile();
	}

	int createFile(const char *fileName, int recordLength) {
		if (recordLength > PAGE_SIZE)
			return RETVAL_ERR;
		if (currentFileHandle.isOpen()) {
			int rc = closeFile(currentFileHandle);
			if (rc != RETVAL_OK) {
				cerr << "Close File Failed!" << endl;
				exit(1);
			}
		}

		int fileID, index;
		fileManager->createFile(fileName);
		fileManager->openFile(fileName, fileID);

		MetadataPageInfo* metadata = (MetadataPageInfo*)(bufPageManager)->allocPage(fileID, 0, index);
		bufPageManager->markDirty(index);
		metadata->pageCount = 2;
		metadata->recordLength = recordLength;
		metadata->recordCount = 0;
		metadata->nextAvailPage = 1;
		metadata->pageSlotNumber = PAGE_SLOT_COUNT / recordLength;
		BufType secondPage = bufPageManager->allocPage(fileID, 1, index);
		PageInfo* pg = (PageInfo*)secondPage;
		bufPageManager->markDirty(index);
		pg->pageNumber = 1;
		pg->nextAvailPage = 0;

		bufPageManager->close();
		fileManager->closeFile(fileID);

		return RETVAL_OK;
	}

	int destroyFile(const char *fileName) {
		//int rc = fileManager->destroyFile(fileName);
		return RETVAL_OK;
	}

	int renameFile(const char *fileNameA, const char *fileNameB) {
		if (currentFileHandle.isOpen()) {
			int rc = closeFile(currentFileHandle);
			if (rc != RETVAL_OK) {
				cerr << "Close File Failed!" << endl;
				exit(1);
			}
		}
		int rc = fileManager->renameFile(fileNameA, fileNameB);
		if (rc != RETVAL_OK)
			return RETVAL_ERR;
		return RETVAL_OK;
		// int fileID;
		// RETURNIF(fileManager->openFile(fileNameB, fileID));
		// FirstPageInfo firstPageHandle(fileID, bufPageManager);
		// firstPageHandle.init(recordSize);
		// bufPageManager->close();
		// RETURNIF(fileManager->closeFile(fileID));
	}

	FileHandler* openFile(const char* fileName) {
		if (currentFileHandle.isOpen()) {
			int rc = closeFile(currentFileHandle);
			if (rc != RETVAL_OK) {
				cerr << "Close File Failed!" << endl;
				exit(1);
			}
		}

		int rc = openFile(fileName, currentFileHandle);
		if (rc != RETVAL_OK) {
			cerr << "Open File Failed!" << endl;
			exit(1);
		}
		return &currentFileHandle;
	}

	int closeFile() {
		if (currentFileHandle.isOpen())
		{
			RETURNIF(closeFile(currentFileHandle));
		}
		return RETVAL_OK;
	}
	BufPageManager *bufPageManager;
	FileManager *fileManager;

private:
	static GlobalFileHandler *recordManager;

	FileHandler currentFileHandle;

	GlobalFileHandler() {
		fileManager = new FileManager();
		bufPageManager = new BufPageManager(fileManager);
	}

	GlobalFileHandler(const GlobalFileHandler &) { }

	GlobalFileHandler &operator=(const GlobalFileHandler &) { return *this; }

	int openFile(const char *fileName, FileHandler &fileHandle) {

		int fileID;
		RETURNIF(fileManager->openFile(fileName, fileID));
		currentFileHandle = FileHandler(bufPageManager, fileID);
		return RETVAL_OK;
	}

	int closeFile(FileHandler &fileHandle) {
		bufPageManager->close();
		RETURNIF(fileManager->closeFile(fileHandle.getFileID()));
		fileHandle.release();
		return RETVAL_OK;
	}
};


#endif //DATABASE_RECORDMANAGER_H
