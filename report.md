<title>数据库系统概论大作业实验报告</title>

<author>组长：2017011404 袁杰 \\ 组员：2017011313 刘丰源 \\ 组员：2017011306 尹凌峰</author>

[maketitle]

[toc]

后续维护该文档时，请保持该格式。

# 分工

- 记录管理：刘丰源
- 索引管理：尹凌峰
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

# 索引管理

## 索引存储

> BTree.hpp

### 存储方式

所有的索引在逻辑上组成一个B+树。B+树的节点使用记录管理模块来存储。每一条记录的data就是一个节点的内容。第一条记录的data存储索引的元数据，包括属性个数、类型、B+树的root。  
对于非叶节点，使用两个vector记录key、child的存储位置。  
对于叶节点，使用两个vector记录索引值以及对应的实际记录的位置。

## 索引操作

> IndexHandler.hpp

### 索引的创建(Create_Index)

使用数据Table名和索引对应的列组合为文件名，创建对应文件，写入元数据和root。

### 索引删除(Delete_Index)

由于文件系统没有删除文件的接口，目前还未实现。

### 索引的打开(Open_Index)

打开索引对应文件，读入元数据，创建并返回一个BTree类。

### 索引的关闭(Close_Index)

直接释放BTree类变量。

> BTree.hpp

### 索引的插入(Insert_Record)

先申请一个record空间，存储索引的内容，之后插入到BTree的正确位置，插入后更新BTree相关节点。

### 索引的删除(Delete_Record)

先判断是否存在对应索引。如果存在就按BTree的删除操作，删除对应索引，并更新BTree相关节点；否则返回更新失败。

### 索引的更新(Update_Record)

先判断是否存原索引。如果存在就执行原索引的删除、新索引的插入；否则返回更新失败。

### 索引的查找(Find_Record)

我们的索引目前支持联合索引，但由于BTree的顺序，所以在查找时只按照第一个索引的大小确定递归查找的节点。在叶节点再对索引判断是否符合查找要求。而且对于一个列只支持一个查找条件，包括大于、小于、等于、大于等于、小于等于、是否null。