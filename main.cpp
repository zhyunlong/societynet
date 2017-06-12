#include "head.h"
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

//利用哈希表存储用户信息 ID作为主关键字是不会重复的 对ID利用哈希函数处理

void showhashinfo(HashTable *hashTable, int id);
void changehashinfo(HashTable *hashTable, int id);
void inithashinfo(Social_Networking SN, HashTable *hashTable);
int  HashSearch(HashTable *hashTable, int data);
void insert(HashTable *hashTable, int data);
bool inithash(HashTable *hashTable, int n);
int Hash(int data);
void insert(HashTable *hashTable, int data);
int  HashSearch(HashTable *hashTable, int data);


void initnet(Social_Networking &SN)
{
	SN.arcnum = 0;
	SN.usernum = 0;
	cout << "请输入网络中用户数量" << endl;
	cin >> SN.usernum;
	for (int i = 0;i < SN.usernum;i++)
	{
		SN.ID[i] = -1;
	}
	for (int i = 0;i < SN.usernum;i++)
	{
		for (int j = 0;j < SN.usernum;j++)
		{
			SN.net[i][j] = 0;//0表示无好友关系
		}//在图中存储信息 以后再构造哈希表 用来查找
	}
}

void buildNet(Social_Networking &SN)
{
	//为每个用户生成唯一的ID号（四位纯数字）
	int random;
	for (int i = 0;i < SN.usernum;i++)
	{
		do {
		random = rand();
		} while (random < 10000);
		SN.ID[i] = random % 10000;
		for (int j = 0;j < i;j++)
		{
			if (SN.ID[i] == SN.ID[j])
			{
				j = 0;
				do {
					random = rand();
				} while (random < 10000);
				SN.ID[i] = random % 10000;
			}
		}
	}
	for (int i = 0;i < SN.usernum;i++)
	{
		SN.net[i][i] = 0;
	}
	for (int i = 0;i < SN.usernum;i++)
	{
		for (int j = i+1;j < SN.usernum;j++)
		{
			if (rand() % 5 == 0)
			{
				SN.net[i][j] = 1;
				SN.arcnum++;
			}
			else
				SN.net[i][j] = 0;
			SN.net[j][i] = SN.net[i][j];
		}
	}
}

void printNet(Social_Networking &SN)
{
	for (int i = 0;i < SN.usernum;i++)
	{
		cout << "用户" << i + 1 << ": " << SN.ID[i];
	}
	cout << endl;
	for (int i = 0;i < SN.usernum;i++)
	{
		for (int j = 0;j < SN.usernum;j++)
		{
			cout << SN.net[i][j] << "  " ;
		}
		cout << endl;
	}
}

void fri(Social_Networking &SN,int id)
{
	
}

int main()
{
	srand(time(0));
	Social_Networking sn;
	HashTable hash;
	inithash(&hash, 5);	
	inithashinfo(sn, &hash);
	int choose;
	do
	{
		cout << "**************************简单社交网络分析系统************************" << endl;
		cout << "***                                                                ***" << endl;
		cout << "***                       1.初始化生成网络                         ***" << endl;
		cout << "***                       2.用户信息修改                           ***" << endl;
		cout << "***                       3.打印显示网络（矩阵形式）               ***" << endl;
		cout << "***                       4.网络分析功能                           ***" << endl;
		cout << "***                       5.好友推荐功能                           ***" << endl;
		cout << "***                       6.退出                                   ***" << endl;
		cout << "***                                                                ***" << endl;
		cout << "**************************简单社交网络分析系统************************" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:
			initnet(sn);
			buildNet(sn);
			break;
		case 2:
			changehashinfo(&hash ,1478 );
		case 3:
			printNet(sn);
			cout << "输入任意值返回" << endl;
			char a;
			cin >> a;
			break;
		case 4:
			showhashinfo(&hash, 1478);
			cout << "输入任意值返回" << endl;
			cin >> a;
			break;
		default:
			break;
		}
		system("cls");
	} while (choose != 6);
}