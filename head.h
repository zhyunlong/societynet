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
	user *elem; //����Ԫ�ش洢��ַ  
	int count;//��ǰԪ�ظ���  
}HashTable;

int L = 0;