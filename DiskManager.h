#pragma once
#include <iostream>
#include "config.h"
using namespace std;

class DiskManager {

private:
	char* addr_system; // start address of system
	SuperBlock* addr_super_block; // start address of super block
	char* inode_bitmap; // start address of inode bitmap
	char* block_bitmap; // start address of block bitmap
	char* addr_block; // start address of blocks
	int root_inode_id; // root directory

public:
	DiskManager();
	~DiskManager();
	INODE* inodes; // series of inode objects
	void createInode(int inode_id, string type, string name, int size, int par_id); // create a new inode
	char* getAddrSystem(); // get the start address of system
	char* getBlockAddrById(int block_id); // get an address of a block by id
	int getBlockIdByAddr(char* block_ad); // get a block id by address
	INODE* getInodeAddrById(int inode_id); // get an address of an inode by id
	void setBlockBitmap(int block_id, bool flag); // set the bitmap value of one block by id
	void setInodeBitmap(int inode_id, bool flag); // set the bitmap value of one inode by id
	int getBlockBitmap(int block_id); // get the bitmap value of one block by id
	int getInodeBitmap(int inode_id); // get the bitmap value of one inode by id
	int getFreeInode(); // return a free inode
	int getFreeBlock(); // return a free block
	void reboot(); // reload data from the local store
};