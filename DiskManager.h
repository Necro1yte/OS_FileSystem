#pragma once
#include <iostream>
#include "config.h"
using namespace std;

class DiskManager {

private:
	char* addr_system; // start address of system
	SuperBLock* addr_super_block; // start address of super block
	char* inode_bitmap; // start address of inode bitmap
	char* block_bitmap; // start address of block bitmap
	INODE* inodes; // start address of inodes
	char* addr_block; // start address of blocks
	int root_inode_id; // root directory

public:
	DiskManager();
	~DiskManager();
	void createInode(int inode_id, string type, char* name, int size, int par_id);
	char* getBlockAddrById(int block_id);
	INODE* getInodeAddrById(int inode_id);
	void setBlockBitmap(int block_id, bool flag);
	void setInodeBitmap(int inode_id, bool flag);
	int getBlockBitmap(int block_id);
	int getInodeBitmap(int inode_id);
	int getFreeInode();
	int getFreeBlock();

};