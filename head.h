#pragma once
#include <iostream>
#include <string>

#define MAX 100

using namespace std;

typedef struct user
{

	int ID;
	int sex;
	string name;
	int birth;
}user;

typedef struct 
{
	user *elem;
	int count;
}HashTable;

typedef struct
{
	int net[MAX][MAX];
	int ID[MAX];
	int usernum;
	int arcnum;
}Social_Networking;



