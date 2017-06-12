#include "head.h"
#include <time.h>
#include <iostream>
#include <string>
#include <algorithm>

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
			if (rand() % 3 == 0)
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

void insertstack(stack &st, int b)
{
	st.top++;
	st.a[st.top] = b;
}

int gettop(stack &st)
{
	return st.a[st.top];
}

void fri(Social_Networking &SN,int id)
{
	int i,k;
	stack st;
	int a[MAX] = { 0 }, b[MAX] = { 0 };
	for (i = 0;i < SN.usernum;i++)
	{
		if (SN.ID[i] == id)
		break;
	}//获取其下标
	for (int j = 0;j < SN.usernum;j++)
	{
		if (SN.net[i][j] == 1)
		{
			a[j]++;
		}
	}//获取其好友
	for (int j = 0;j < SN.usernum;j++)
	{
		if (a[j] == 1)
		{
			//遍历搜索i的好友j满足是j的好友但不是i的好友的数目，取值最大的为其推荐好友
			for (k = 0;k < SN.usernum;k++)
			{
				if (SN.net[j][k] == 1 && SN.net[i][k] == 0 && k!=i)
				{
					b[k]++;
				}
			}
		}
	}
	st.top = 0;
	insertstack(st, b[0]);
	int pos = 0;
	for (int j = 1;j < SN.usernum;j++)
	{
		if (b[j] > st.a[st.top])
		{
			pos = j;
			//deletstack(st);
			insertstack(st, b[j]);
		}
	}
	cout << "推荐好友为ID为" << SN.ID[pos] << "的用户" << endl;
	cout << " 你们拥有" << gettop(st) << "个共同好友" << endl;
}



void friendlist(Social_Networking &SN, int id)
{
	int i;
	int a[MAX] = { 0 };
	for (i = 0;i < SN.usernum;i++)
	{
		if (SN.ID[i] == id)
			break;
	}//获取其下标
	for (int j = 0;j < SN.usernum;j++)
	{
		if (SN.net[i][j] == 1)
		{
			a[j]++;
		}
	}//获取其好友
	cout << "好友列表：" << endl;
	for (int j = 0;j < SN.usernum;j++)
	{
		if (a[j] == 1)
		{
			cout << "用户" << SN.ID[j]<<"  ";
		}
	}
}

bool idtest(Social_Networking &SN, int id)
{
	int flag = 0;
	for (int i = 0;i < SN.usernum;i++)
	{
		if (id == SN.ID[i])
			flag = 1;
	}
	if (flag == 0)
		return false;
	if (flag == 1)
		return true;
}

int main()
{
	//srand(time(0));
	Social_Networking sn;
	HashTable hash;
	inithash(&hash, 5);	
	inithashinfo(sn, &hash);
	int choose,id;
	do
	{
		cout << "**************************简单社交网络分析系统************************" << endl;
		cout << "***                                                                ***" << endl;
		cout << "***                       1.初始化生成网络                         ***" << endl;
		cout << "***                       2.用户信息修改                           ***" << endl;
		cout << "***                       3.打印显示网络（矩阵形式）               ***" << endl;
		cout << "***                       4.用户信息查询                           ***" << endl;
		cout << "***                       5.好友推荐功能                           ***" << endl;
		cout << "***                       6.网络分析                               ***" << endl;
		cout << "***                       7.退出                                   ***" << endl;
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
			cout << "请输入想要展示的用户ID" << endl;
			cin >> id;
			while (idtest(sn, id))
			{
				cout << "id输入错误，请重新输入" << endl;
				cin >> id;
			}
			changehashinfo(&hash ,id );
			break;
		case 3:
			printNet(sn);
			cout << "输入任意值返回" << endl;
			char a;
			cin >> a;
			break;
		case 4:
			cout << "请输入想要修改的用户ID" << endl;
			cin >> id;
			while (idtest(sn, id))
			{
				cout << "id输入错误，请重新输入" << endl;
				cin >> id;
			}
			//showhashinfo(&hash, id);
			friendlist(sn, id);
			cout << endl;
			cout << "输入任意值返回" << endl;
			cin >> a;
			break;
		case 5:
			cout << "请输入用户ID" << endl;
			cin >> id;
			while (idtest(sn, id))
			{
				cout << "id输入错误，请重新输入" << endl;
				cin >> id;
			}
			fri(sn, id);
			cin >> a;
		default:
			break;
		}
		system("cls");
	} while (choose != 6);
}