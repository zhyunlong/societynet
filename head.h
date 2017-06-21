#pragma once
#include <iostream>
#include <string>

#define MAX 100
#define INFINITY  65535


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

typedef struct 
{
	double a[MAX];
	int top;
	int number;
} stack;