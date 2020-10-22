<title>数据库系统概论大作业实验报告</title>

<author>组长：2017011404 袁杰 \\ 组员：2017011313 刘丰源 \\ 组员：2017011306 尹凌峰</author>

[maketitle]

[toc]

后续维护该文档时，请保持该格式。

# 分工

- 记录管理：刘丰源
- 索引管理（TODO）：尹凌峰
- 系统管理（TODO）：袁杰
- 查询解析（TODO）：袁杰

# 记录管理

## 文件管理

> main.cpp

通过调用 FileManager 提供的接口进行文件管理，进行简单的包装即可。

如果是创建文件，则需要同时创建文件的元数据，元数据为文件所拥有页面的第一页（编号 0）。创建完元数据后，再分配一个空闲页面，用于以后保存记录。

## 页面管理

> PageInfo.h

元数据通过结构体 MetadataPageInfo 的格式进行保存，记录数据页面通过结构体 PageInfo 的格式进行保存。

```cpp
/* 提供的 filesystem 每次分配的页面大小为 8kb
 * 折合为 2048 个 uint
 * nextAvailPage 和 pageNumber 用两个
 * bitmap 和 data 共 2046 个
 * 1984 + 62 == 2046
 * 1984 == 62 * sizeof(uint) * 8
 */
const uint PAGE_SLOT_COUNT = 1984;
struct PageInfo {
    uint nextAvailPage;
    uint pageNumber;
    uint bitmap[62];
    uint data[PAGE_SLOT_COUNT];
}
```

## 记录保存

> Record.hpp

通过结构体 Record 进行保存。

由于 Record 的长度不是固定的，所以内存需要动态分配。这就带来了一些内存问题，比如构造函数、析构函数、赋值操作，需要特别注意一下。

## 记录操作

> FileHandler.hpp

### 修改操作（modifyRecord）

直接找到对应的记录进行修改。

### 查询操作（selectRecord）

遍历所有记录进行查询。

### 插入操作（insertRecord）

metadata->nextAvailPage 内一定有空闲的位置存放该记录，直接复制进去即可。

复制后需要检察当前页面是否有足够的空间用于未来再放一条记录，如果没有，则需要分配一个页面。

### 删除操作（deleteRecord）

找到该记录所在的页面，把 bitmap 对应的位置置零即可。

删除后该页面就有了空闲的位置，将页面的 nextAvailPage 设置为 matadata->nextAvailPage ，然后将 matadata->nextAvailPage 设置为该页面的页号。
