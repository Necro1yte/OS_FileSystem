#pragma once
#include <iostream>
using namespace std;

string getTime() {
	time_t time_seconds = time(0);
	struct tm now_time;
	localtime_s(&now_time, &time_seconds);

	string time = to_string(now_time.tm_year + 1900)+ "/" + to_string(now_time.tm_mon + 1) + "/" + to_string(now_time.tm_mday) + " " + to_string(now_time.tm_hour) + ":" + to_string(now_time.tm_min) + ":" + to_string(now_time.tm_sec);
	return time;
}

int getIntFromChar(const char ch[3]) {
	char ch_int[4];
	int x = 0;
	memset(ch_int, 0, 4 * sizeof(char));
	memcpy(ch_int, ch, 3 * sizeof(char));
	memcpy(&x, ch_int, 3 * sizeof(char));
	return x;
}

void getCharFromInt(const int x, char* ch_int) {
	char ch[4];
	memset(ch, 0, 4 * sizeof(char));
	memcpy(ch, &x, 4 * sizeof(char));
	memcpy(ch_int, ch, 3 * sizeof(char));
}