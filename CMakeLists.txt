cmake_minimum_required(VERSION 3.10)
project(database)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DYYERROR_VERBOSE")

set(SOURCE_FILES
        src/global.h
        filesystem/bufmanager/BufPageManager.h
        filesystem/bufmanager/FindReplace.h
        filesystem/fileio/FileManager.h
        filesystem/fileio/FileTable.h
        filesystem/utils/compare.h
        filesystem/utils/MyBitMap.h
        filesystem/utils/MyBitMap.cpp
        filesystem/utils/MyHashMap.h
        filesystem/utils/MyLinkList.h
        filesystem/utils/pagedef.h
        src/FileHandler.h
        src/FileHandler.cpp
        src/GlobalFileHandler.h
        src/GlobalFileHandler.cpp
        src/Record.h
        src/Record.cpp
        src/PageInfo.h
        src/PageInfo.cpp
        src/FileScan.h
        src/FileScan.cpp
        src/utils.h
        src/SystemManager.cpp
        src/SystemManager.h
        src/Printer.h
        src/Printer.cpp
        src/RecordDescriptor.h
        src/RecordDescriptor.cpp
        src/DBHandle.h
        src/DBHandle.cpp
        src/parser/lex.yy.cpp
        src/parser/Tree.h
        src/parser/Tree.cpp
        src/parser/parser.tab.hpp
        src/parser/parser.tab.cpp
        src/RecordDescriptor.cpp
        src/RecordDescriptor.h
        src/BTree.hpp
        src/IndexManager.hpp
)

SET_SOURCE_FILES_PROPERTIES(src/parser/lex.yy.cpp PROPERTIES LANGUAGE CXX )

add_executable(database ${SOURCE_FILES} src/main.cpp)
target_link_libraries(database)