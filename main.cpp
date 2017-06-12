#include "head.h"
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

//���ù�ϣ��洢�û���Ϣ ID��Ϊ���ؼ����ǲ����ظ��� ��ID���ù�ϣ��������

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
	cout << "�������������û�����" << endl;
	cin >> SN.usernum;
	for (int i = 0;i < SN.usernum;i++)
	{
		SN.ID[i] = -1;
	}
	for (int i = 0;i < SN.usernum;i++)
	{
		for (int j = 0;j < SN.usernum;j++)
		{
			SN.net[i][j] = 0;//0��ʾ�޺��ѹ�ϵ
		}//��ͼ�д洢��Ϣ �Ժ��ٹ����ϣ�� ��������
	}
}

void buildNet(Social_Networking &SN)
{
	//Ϊÿ���û�����Ψһ��ID�ţ���λ�����֣�
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
		cout << "�û�" << i + 1 << ": " << SN.ID[i];
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
		cout << "**************************���罻�������ϵͳ************************" << endl;
		cout << "***                                                                ***" << endl;
		cout << "***                       1.��ʼ����������                         ***" << endl;
		cout << "***                       2.�û���Ϣ�޸�                           ***" << endl;
		cout << "***                       3.��ӡ��ʾ���磨������ʽ��               ***" << endl;
		cout << "***                       4.�����������                           ***" << endl;
		cout << "***                       5.�����Ƽ�����                           ***" << endl;
		cout << "***                       6.�˳�                                   ***" << endl;
		cout << "***                                                                ***" << endl;
		cout << "**************************���罻�������ϵͳ************************" << endl;
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
			cout << "��������ֵ����" << endl;
			char a;
			cin >> a;
			break;
		case 4:
			showhashinfo(&hash, 1478);
			cout << "��������ֵ����" << endl;
			cin >> a;
			break;
		default:
			break;
		}
		system("cls");
	} while (choose != 6);
}