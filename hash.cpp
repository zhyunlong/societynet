#include "head.h"
#include <string>


int Hash(int data);
void insert(HashTable *hashTable, int data);
int  HashSeneth(HashTable *hashTable, int data);

int L = 0;

bool inithash(HashTable *hashTable, int n)//哈希表的初始化  
{
	int i;
	L = n;
	hashTable->elem = (user*)malloc(L * sizeof(user));//申请内存  
	hashTable->count = L;
	for (i = 0; i < L; i++)
	{
		hashTable->elem[i].birth = -1;
		hashTable->elem[i].ID = -1;
		hashTable->elem[i].sex = -1;
	}
	return true;
}

//哈希函数，除留余数法 
int Hash(int data)
{
	return data % L;//前两位数字与后两位数字之和对L取余数
}

void insert(HashTable *hashTable, int data)
{
	int Addr = Hash(data);//求哈希地址  
	while (hashTable->elem[Addr].ID != -1)//求得地址不是初始化时的空，则表示有元素已经插入，会有冲突  
	{
		Addr = (Addr + 1) % L;//开放地址线性探测，还可以二次探测  
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
	cout << "ID为" << id << "的信息是" << endl;
	cout << "ID为" << hashTable->elem[Addr].ID << endl;
	cout << "性别" << hashTable->elem[Addr].sex << "             (-1为维赋值 0为男 1为女)" <<endl;
	cout << "生日为" << hashTable->elem[Addr].birth << endl;
}

void changehashinfo(HashTable *hashTable, int id)
{
	int Addr, choose = 0;
	Addr = HashSeneth(hashTable, id);
	do {
		cout << "请选择想要修改的信息" << endl;
		cout << "************************************************************" << endl;
		cout << "***                 1.修改性别（0为男，1为女）           ***" << endl;
		cout << "***                       2.修改生日                     ***" << endl;
		cout << "***                       3.返回                         ***" << endl;
		cout << "************************************************************" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:
			cout << "请输入" << endl;
			cin >> hashTable->elem[Addr].name;
			break;
		case 2:
			cout << "请输入" << endl;
			cin >> hashTable->elem[Addr].sex;
			break;
		case 3:
			cout << "请输入" << endl;
			cin >> hashTable->elem[Addr].birth;
			break;
		}
		system("cls");
	} while (choose != 4);
}
