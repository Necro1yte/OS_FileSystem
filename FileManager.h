#pragma once
#include <iostream>
#include "DiskManager.cpp"
using namespace std;

class FileManager {

public:
	FileManager();
	~FileManager();

	void createFile(char * file_name, int file_size); // create a new file
	void deleteFile(char* file_name); // delete a file 
	void createDir(char* file_name); // create a directory
	void deleteDir(char* file_name); // delete a directory
	void changeDir(char* file_name); // change the working directory
	void dir(); // list all the files and sub-directories under current working directory
	void copyFile(char* file_1, char* file_2); // copy to a file from another file
	void sum(); // display the usage of storage space
	void printFile(char* file_name); // print out the content of file

private:
	DiskManager disk;
	int cur_inode;
};