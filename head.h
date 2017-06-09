#pragma once
#include <iostream>

#define MAX 100

using namespace std;

typedef struct
{
	int ID;
	int sex;
	string name;
	string birth;
}user;

typedef struct 
{
	int net[MAX][MAX];
	int ID[MAX];
	int usernum;
	int arcnum;
}Social_Networking;

typedef struct
{
	user *elem; //数据元素存储地址  
	int count;//当前元素个数  
}HashTable;

int L = 0;