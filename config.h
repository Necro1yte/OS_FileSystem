#pragma once
#include <string>
#include <time.h>
#include "tool.h"
using namespace std;

const int SYSTEM_SIZE = 16 * 1024 * 1024; // space of file system
const int BLOCK_SIZE = 1 * 1024; // size of one block
const int BLOCK_NUM = 16 * 1024; // number of blocks
const int ADDR_LENGTH = 3; // length of address
const int INODE_NUM = 47; // number of Inodes
const int INODE_DIRECT_ADDR = 10; // number of direct block address
const int INODE_TABLE_SIZE = INODE_NUM; //size of one directory

const int OFFSET_SUPER_BLOCK = 0; 
const int OFFSET_INODE_BITMAP = OFFSET_SUPER_BLOCK + 1; // one block for super block
const int OFFSET_DBLOCK_BITMAP = OFFSET_INODE_BITMAP + 1; // one block for inode bitmap
const int OFFSET_INODE = OFFSET_DBLOCK_BITMAP + 2; // two blocks for data block bitmap
const int OFFSET_DBLOCK = OFFSET_INODE + 5; // five blocks for inodes
const int DBLOCK_NUM = BLOCK_NUM - OFFSET_DBLOCK; // rest blocks for data blocks

class SuperBLock {
private:
	int magic_num;
	int num_of_inodes;
	int num_of_blocks;
	int start_of_inodes;
};

// length of 
class INODE {

private:
	char type; // type of inode
	char name[20]; // name of inode
	int size; // size of inode
	int parent_inode; // parent inode
	char addr[(INODE_DIRECT_ADDR + 1) * ADDR_LENGTH]; // total address length
	char time_created[20]; // time when creating file

public:
	INODE() {
	}

	void setInodeType(string value) {
		if (value == "file")
			type = '0';
		else if (value == "dir")
			type = '1';
		else
			cout << "inode type error!" << endl;
	}

	string getInodeType() {
		if (type == '0')
			return "file";
		else
			return "dir";
	}

	void setTimeCreated(const char* ch) {
		memcpy(time_created, ch, 20 * sizeof(char));
	}

	char* getTimeCreated() {
		return time_created;
	}

	string getInodeName() {
		return name;
	}

	void setInodeName(char* str) {
		memcpy(name, str, 20 * sizeof(char));
	}

	int getInodeSize() {
		return size;
	}

	void setInodeSize(int sz) {
		size = sz;
	}

	int getParInode() {
		return parent_inode;
	}

	void setParInode(int id) {
		parent_inode = id;
	}

	void setDirectAddr(int idx, int block_id) {
		char chr[3];
		getCharFromInt(block_id, chr);
		memcpy(addr + idx * ADDR_LENGTH * sizeof(char), chr, ADDR_LENGTH * sizeof(char));
	}

	int getDirectAddr(int idx) {
		return getIntFromChar(addr + idx * ADDR_LENGTH * sizeof(char));
	}

	void setIndirectAddr(int block_id) {
		char chr[3];
		getCharFromInt(block_id, chr);
		memcpy(addr + INODE_DIRECT_ADDR * ADDR_LENGTH * sizeof(char), chr, ADDR_LENGTH * sizeof(char));
	}

	int getIndirectAddr() {
		return getIntFromChar(addr + INODE_DIRECT_ADDR * ADDR_LENGTH * sizeof(char));
	}
};