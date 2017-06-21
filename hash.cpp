#include "head.h"
#include <string>


int Hash(int data);
void insert(HashTable *hashTable, int data);
int  HashSeneth(HashTable *hashTable, int data);

int L = 0;

bool inithash(HashTable *hashTable, int n)//��ϣ��ĳ�ʼ��  
{
	int i;
	L = n;
	hashTable->elem = (user*)malloc(L * sizeof(user));//�����ڴ�  
	hashTable->count = L;
	for (i = 0; i < L; i++)
	{
		hashTable->elem[i].birth = -1;
		hashTable->elem[i].ID = -1;
		hashTable->elem[i].sex = -1;
	}
	return true;
}

//��ϣ���������������� 
int Hash(int data)
{
	return data % L;//ǰ��λ���������λ����֮�Ͷ�Lȡ����
}

void insert(HashTable *hashTable, int data)
{
	int Addr = Hash(data);//���ϣ��ַ  
	while (hashTable->elem[Addr].ID != -1)//��õ�ַ���ǳ�ʼ��ʱ�Ŀգ����ʾ��Ԫ���Ѿ����룬���г�ͻ  
	{
		Addr = (Addr + 1) % L;//���ŵ�ַ����̽�⣬�����Զ���̽��  
	}
	hashTable->elem[Addr].ID = data;
}

int  HashSeneth(HashTable *hashTable, int data)
{
	int Addr = Hash(data);
	while (hashTable->elem[Addr].ID != data)
	{
		Addr = (Addr + 1) % L;
		if (hashTable->elem[Addr].ID == -1 || Addr == Hash(data))
			return -1;
	}
	return Addr;
}

void inithashinfo(Social_Networking SN, HashTable *hashTable)
{
	for (int i = 0;i < SN.usernum;i++)
	{
		insert(hashTable, SN.ID[i]);
	}
}

void showhashinfo(HashTable *hashTable, int id)
{
	int Addr;
	Addr = HashSeneth(hashTable, id);
	cout << "IDΪ" << id << "����Ϣ��" << endl;
	cout << "IDΪ" << hashTable->elem[Addr].ID << endl;
	cout << "�Ա�" << hashTable->elem[Addr].sex << "             (-1Ϊά��ֵ 0Ϊ�� 1ΪŮ)" <<endl;
	cout << "����Ϊ" << hashTable->elem[Addr].birth << endl;
}

void changehashinfo(HashTable *hashTable, int id)
{
	int Addr, choose = 0;
	Addr = HashSeneth(hashTable, id);
	do {
		cout << "��ѡ����Ҫ�޸ĵ���Ϣ" << endl;
		cout << "************************************************************" << endl;
		cout << "***                 1.�޸��Ա�0Ϊ�У�1ΪŮ��           ***" << endl;
		cout << "***                       2.�޸�����                     ***" << endl;
		cout << "***                       3.����                         ***" << endl;
		cout << "************************************************************" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:
			cout << "������" << endl;
			cin >> hashTable->elem[Addr].name;
			break;
		case 2:
			cout << "������" << endl;
			cin >> hashTable->elem[Addr].sex;
			break;
		case 3:
			cout << "������" << endl;
			cin >> hashTable->elem[Addr].birth;
			break;
		}
		system("cls");
	} while (choose != 4);
}
