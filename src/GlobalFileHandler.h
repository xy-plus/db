#pragma once

#include "global.h"
#include "FileHandler.h"

class FileManager;

class GlobalFileHandler {
public:
	static GlobalFileHandler *instance();

	static void resetInstance();

	~GlobalFileHandler();

	int createFile(const char *fileName, int recordLength);

	int destroyFile(const char *fileName);

	int renameFile(const char *fileNameA, const char *fileNameB);

	FileHandler* openFile(const char* fileName);

	int closeFile();
	BufPageManager *bufPageManager;
	FileManager *fileManager;

private:
	static GlobalFileHandler *recordManager;

	FileHandler currentFileHandle;

	GlobalFileHandler();

	GlobalFileHandler(const GlobalFileHandler &);

	GlobalFileHandler &operator=(const GlobalFileHandler &);

	int openFile(const char *fileName, FileHandler &fileHandle);

	int closeFile(FileHandler &fileHandle);
};
