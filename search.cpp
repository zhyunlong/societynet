#include "head.h"

bool init(HashTable *hashTable, int n)//��ϣ��ĳ�ʼ��  
{
	int i;
	L = n;
	hashTable->elem = (user*)malloc(L * sizeof(user));//�����ڴ�  
	hashTable->count = L;
	for (i = 0; i < L; i++)
	{
		hashTable->elem[i].birth = 'null';
		hashTable->elem[i].name = 'null';
		hashTable->elem[i].ID = -1;
		hashTable->elem[i].sex = -1;
	}
	return true;
}

//��ϣ���������������� 
int Hash(int data)
{
	return data%L;
}

void insert(HashTable *hashTable, int data)
{
	int Addr = Hash(data);//���ϣ��ַ  
	while (hashTable->elem[Addr] != -1)//��õ�ַ���ǳ�ʼ��ʱ�Ŀգ����ʾ��Ԫ���Ѿ����룬���г�ͻ  
	{
		Addr = (Addr + 1) % L;//���ŵ�ַ����̽�⣬�����Զ���̽��  
	}
	hashTable->elem[Addr] = data;
}

int  HashSearch(HashTable *hashTable, int data)
{
	int Addr = Hash(data);
	while (hashTable->elem[Addr] != data)
	{
		Addr = (Addr + 1) % L;
		if (hashTable->elem[Addr] == -1 || Addr == Hash(data))
			return -1;
	}
	return Addr;
}
