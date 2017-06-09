#include "head.h"

bool init(HashTable *hashTable, int n)//哈希表的初始化  
{
	int i;
	L = n;
	hashTable->elem = (user*)malloc(L * sizeof(user));//申请内存  
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

//哈希函数，除留余数法 
int Hash(int data)
{
	return data%L;
}

void insert(HashTable *hashTable, int data)
{
	int Addr = Hash(data);//求哈希地址  
	while (hashTable->elem[Addr] != -1)//求得地址不是初始化时的空，则表示有元素已经插入，会有冲突  
	{
		Addr = (Addr + 1) % L;//开放地址线性探测，还可以二次探测  
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
