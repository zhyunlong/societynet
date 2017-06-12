#include "head.h"
#include <time.h>
#include <iostream>
#include <string>
#include <algorithm>

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
	}//��ȡ���±�
	for (int j = 0;j < SN.usernum;j++)
	{
		if (SN.net[i][j] == 1)
		{
			a[j]++;
		}
	}//��ȡ�����
	for (int j = 0;j < SN.usernum;j++)
	{
		if (a[j] == 1)
		{
			//��������i�ĺ���j������j�ĺ��ѵ�����i�ĺ��ѵ���Ŀ��ȡֵ����Ϊ���Ƽ�����
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
	cout << "�Ƽ�����ΪIDΪ" << SN.ID[pos] << "���û�" << endl;
	cout << " ����ӵ��" << gettop(st) << "����ͬ����" << endl;
}



void friendlist(Social_Networking &SN, int id)
{
	int i;
	int a[MAX] = { 0 };
	for (i = 0;i < SN.usernum;i++)
	{
		if (SN.ID[i] == id)
			break;
	}//��ȡ���±�
	for (int j = 0;j < SN.usernum;j++)
	{
		if (SN.net[i][j] == 1)
		{
			a[j]++;
		}
	}//��ȡ�����
	cout << "�����б�" << endl;
	for (int j = 0;j < SN.usernum;j++)
	{
		if (a[j] == 1)
		{
			cout << "�û�" << SN.ID[j]<<"  ";
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
		cout << "**************************���罻�������ϵͳ************************" << endl;
		cout << "***                                                                ***" << endl;
		cout << "***                       1.��ʼ����������                         ***" << endl;
		cout << "***                       2.�û���Ϣ�޸�                           ***" << endl;
		cout << "***                       3.��ӡ��ʾ���磨������ʽ��               ***" << endl;
		cout << "***                       4.�û���Ϣ��ѯ                           ***" << endl;
		cout << "***                       5.�����Ƽ�����                           ***" << endl;
		cout << "***                       6.�������                               ***" << endl;
		cout << "***                       7.�˳�                                   ***" << endl;
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
			cout << "��������Ҫչʾ���û�ID" << endl;
			cin >> id;
			while (idtest(sn, id))
			{
				cout << "id�����������������" << endl;
				cin >> id;
			}
			changehashinfo(&hash ,id );
			break;
		case 3:
			printNet(sn);
			cout << "��������ֵ����" << endl;
			char a;
			cin >> a;
			break;
		case 4:
			cout << "��������Ҫ�޸ĵ��û�ID" << endl;
			cin >> id;
			while (idtest(sn, id))
			{
				cout << "id�����������������" << endl;
				cin >> id;
			}
			//showhashinfo(&hash, id);
			friendlist(sn, id);
			cout << endl;
			cout << "��������ֵ����" << endl;
			cin >> a;
			break;
		case 5:
			cout << "�������û�ID" << endl;
			cin >> id;
			while (idtest(sn, id))
			{
				cout << "id�����������������" << endl;
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