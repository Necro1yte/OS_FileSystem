#include "DiskManager.h"

DiskManager::DiskManager() {
	// allocate space for system
	addr_system = (char*)malloc(SYSTEM_SIZE * sizeof(char));

	// allocate address for super block
	addr_super_block = (SuperBLock*)addr_system;

	// allocate space for inode bitmap
	inode_bitmap = addr_system + OFFSET_INODE_BITMAP * BLOCK_SIZE;
	memcpy(inode_bitmap, (new char[INODE_NUM]), INODE_NUM * sizeof(char));
	memset(inode_bitmap, '0', INODE_NUM * sizeof(char));

	// allocate space for data block bitmap
	block_bitmap = addr_system + OFFSET_DBLOCK_BITMAP * BLOCK_SIZE;
	memcpy(block_bitmap, (new char[DBLOCK_NUM]), DBLOCK_NUM * sizeof(char));
	memset(block_bitmap, '0', DBLOCK_NUM * sizeof(char));

	// initialze inodes
	inodes = (INODE*)addr_system + OFFSET_INODE * BLOCK_SIZE;
	memcpy(inodes, (new INODE[INODE_NUM]), INODE_NUM * sizeof(char));
	
	// initialize data block
	addr_block = addr_system + OFFSET_DBLOCK * BLOCK_SIZE;

	// initialize root inode
	root_inode_id = getFreeInode();
	setInodeBitmap(root_inode_id, true);

}

DiskManager::~DiskManager() {
	//FILE* fp;
	//errno_t err = fopen_s(&fp, "backup.dat", "w");
	//fwrite(addr_system, sizeof(char), SYSTEM_SIZE, fp);
	//fclose(fp);

	free(addr_system);
}

void DiskManager::createInode(int inode_id, string type, char* name, int size, int par_id) {
	inodes[inode_id].setInodeType(type);
	inodes[inode_id].setInodeName(name);
	inodes[inode_id].setInodeSize(size);
	inodes[inode_id].setParInode(par_id);
	inodes[inode_id].setTimeCreated(getCurrTime().c_str());
	for (int i = 0; i < INODE_DIRECT_ADDR; i++) {
		inodes[inode_id].setDirectAddr(i, -1);
	}
	inodes[inode_id].setIndirectAddr(-1);
	setInodeBitmap(inode_id, -1);
}

char* DiskManager::getBlockAddrById(int block_id) {
	return addr_block + (block_id * BLOCK_SIZE);
}

INODE* DiskManager::getInodeAddrById(int inode_id) {
	return inodes + inode_id;
}

void DiskManager::setBlockBitmap(int block_id, bool flag) {
	if (flag) 
		block_bitmap[block_id] = '1';
	else 
		block_bitmap[block_id] = '0';
}

void DiskManager::setInodeBitmap(int inode_id, bool flag) {
	if (flag) 
		inode_bitmap[inode_id] = '1';
	else 
		inode_bitmap[inode_id] = '0';
	
}

int DiskManager::getBlockBitmap(int block_id) {
	if (block_bitmap[block_id] == '1')
		return 1;
	else
		return 0;
}

int DiskManager::getInodeBitmap(int inode_id) {
	if (inode_bitmap[inode_id] == '1')
		return 1;
	else
		return 0;
}

int DiskManager::getFreeInode() {
	int free_id = -1;
	for (int i = 0; i < INODE_NUM; i++) {
		if (inode_bitmap[i] == '0')
			free_id = i;
	}
	return free_id;
}

int DiskManager::getFreeBlock() {
	int free_id = -1;
	for (int i = 0; i < DBLOCK_NUM; i++) {
		if (block_bitmap[i] == '0')
			free_id = i;
	}
	return free_id;
}


