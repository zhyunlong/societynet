#include "head.h"
#include <time.h>
#include <iostream>
#include <iomanip>
#include <algorithm>


#define INFINITY  65535

using namespace std;


int final[MAX][MAX], path[MAX][MAX] = {-1};

//���ù�ϣ��洢�û���Ϣ ID��Ϊ���ؼ����ǲ����ظ��� ��ID���ù�ϣ��������

void showhashinfo(HashTable *hashTable, int id);
void changehashinfo(HashTable *hashTable, int id);
void inithashinfo(Social_Networking SN, HashTable *hashTable);
int  HashSeneth(HashTable *hashTable, int data);
void insert(HashTable *hashTable, int data);
bool inithash(HashTable *hashTable, int n);
int Hash(int data);
int  HashSeneth(HashTable *hashTable, int data);

int visited[MAX];
void DFS(Social_Networking SN, int a);

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
				if (SN.ID[i] < 10000)
					SN.ID[i] = SN.ID[i] * 10;
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
				SN.net[i][j] = rand()%15+1;
				SN.arcnum++;
			}
			else
				SN.net[i][j] = INFINITY;
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
			cout <<setw(8) << SN.net[i][j] ;
		}
		cout << endl;
	}
}

void Linknet(Social_Networking &SN)
{
	DFS(SN,0);
	int a;
	for (int i = 0;i < SN.usernum;i++)
	{
		if (visited[i] == 1)
		{
			a = i;
			break;
		}
	}
	for (int i = 0;i < SN.usernum;i++)
	{
		if (visited[i] == 0)
		{
			SN.net[a][i] = rand() % 15;
			SN.net[i][a] = SN.net[a][i];
		}
	}
}

void insertstack(stack &st, double b)
{
	st.top++;
	st.a[st.top] = b;
}

void initstack(stack &st)
{
	st.top = 0;
}

void deletstack(stack &st)
{
	if (st.top != 0)
	{
		st.top--;
	}
	else
		cout << "error" << endl;
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
		if (SN.net[i][j] != INFINITY&&SN.net[i][j] != 0)
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
				if (SN.net[j][k] != INFINITY && SN.net[j][k] != 0 && SN.net[i][k] == INFINITY && k!=i)
				{
					b[k]++;
				}
			}
		}
	}
	initstack(st);
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
		if (SN.net[i][j] != INFINITY&&SN.net[i][j] != 0)
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
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		return false;
	if (flag == 1)
		return true;
}
void initvisited(Social_Networking SN)
{
	for (int i = 0;i < SN.usernum;i++)
	{
		visited[i] = 0;
	}
}


void DFS(Social_Networking SN,int a)
{
	stack st;
	int tmp,flag=0;
	initstack(st);
	//if(visited[a]!=1)
	visited[a] = 1;
	//cout << a;
	insertstack(st, a);
	while (st.top!=0)
	{
		int i;
		flag = 0;
		tmp = gettop(st);
		for (i = 0;i < SN.usernum;i++)
		{
			if (SN.net[tmp][i] != 0 && SN.net[tmp][i] != INFINITY && visited[i] == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 1)
		{
			//cout << i;
			visited[i] = 1;
			insertstack(st, i);
		}
		else if(i==SN.usernum)
			deletstack(st);
	}
}

int analysecircl(Social_Networking SN)
{
	int num=0;
	for (int i = 0;i < SN.usernum;i++)
	{
		if (!visited[i])
		{
			DFS(SN, i);
			num++;
		}
	}
	return num;
}

void shortestpath_floyd(Social_Networking sn)
{
	int tmp, a, b, c, d, flag = 0;
	for (int i = 0;i < sn.usernum;i++)
	{
		for (int j = 0;j < sn.usernum;j++)
		{
			final[i][j] = sn.net[i][j];
			if (sn.net[i][j] != INFINITY)
				path[i][j] = j;
		}
	}
	/*for (int i = 1;i < sn.usernum;i++)
	{
		for (int j = i - 1;j >= 0; j--)
		{
			final[i][j] = sn.net[j][i];
		}
	}*/
	for (int k = 0;k < sn.usernum;k++)
	{
		for (int i = 0;i < sn.usernum;i++)
		{
			for (int j = 0;j < sn.usernum;j++)
			{
				tmp = (final[i][k] == INFINITY || final[k][j] == INFINITY) ? INFINITY : (final[i][k] + final[k][j]);
				if (tmp < final[i][j])
				{
					final[i][j] = tmp;
					path[i][j] = path[i][k];
				}
			}
		}
	}
	cout << "�����������̾���: " << endl;
	for (int i = 0; i < sn.usernum; i++)
	{
		for (int j = 0; j < sn.usernum; j++)
			cout << setw(2) << final[i][j] << "  ";
		cout << endl;
	}
	for (int v = 0; v<sn.usernum; ++v)
	{
		for (int w = 0; w<sn.usernum; w++)
		{
			int k;
			printf("v%d-v%d weight: %d ", v, w, final[v][w]);
			k = path[v][w];                
			printf(" path: %d", v);    
			while(k!=w)
			{
				printf(" -> %d", k);    
				k = path[k][w];            
			}
			printf(" -> %d\n", w);    
		}
		printf("\n");
	}
}


void degree_centrality(Social_Networking sn)
{
	int degree[MAX] = { 0 };
	stack st;
	for (int i = 0;i < sn.usernum;i++)
	{
		for (int j = 0;j < sn.usernum;j++)
		{
			if (sn.net[i][j] != 0 && sn.net[i][j]!=INFINITY)
				degree[i]++;
		}
	}
	cout << endl;
	initstack(st);
	insertstack(st, degree[0]);
	int pos = 0;
	for (int j = 1;j < sn.usernum;j++)
	{
		if (degree[j] > st.a[st.top])
		{
			pos = j;
			//deletstack(st);
			insertstack(st, degree[j]);
		}
	}
	for (int i = 0;i < sn.usernum;i++)
	{
		cout << degree[i] << "  ";
	}
	cout << "�ؼ����degree��IDΪ" << sn.ID[pos] << "���û�" << endl;
}

void closeness_centrality(Social_Networking sn)
{
	stack st;
	shortestpath_floyd(sn);
	double closeness[MAX] = { 0 };
	for (int i = 0;i < sn.usernum;i++)
	{
		for (int j = 0;j < sn.usernum;j++)
		{
			closeness[i] += final[i][j];
		}
	}
	for (int i = 0;i < sn.usernum;i++)
	{
		closeness[i] = (sn.usernum - 1 )/ closeness[i];
	}
	initstack(st);
	insertstack(st, closeness[0]);
	int pos = 0;
	for (int j = 1;j < sn.usernum;j++)
	{
		if (closeness[j] > st.a[st.top])
		{
			pos = j;
			//deletstack(st);
			insertstack(st, closeness[j]);
		}
	}
	cout << endl;
	cout << "�ؼ����closeness_centrality��IDΪ" << sn.ID[pos] << "���û�" <<st.a[st.top] << endl;
}

void between_centrality(Social_Networking sn)
{
	stack st;
	double between_centrality[MAX];
	double up=0;
	double down=0;
	for (int i = 0;i < sn.usernum;i++)
	{
		down = 0;
		up = 0;
		for (int v = 0; v<sn.usernum; ++v)
		{
			if (v == i)
				continue;
			for (int w = 0; w<sn.usernum; w++)
			{
				if (w == i)
					continue;
				down++;
				int k;
				k = path[v][w];
				if (v == i)
				{
					up++;
					break;
				}
				while (k != w)
				{
					if (k == i)
					{
						up++;
						break;
					}
					k = path[k][w];
				}
				if (w == i)
				{
					up++;
					break;
				}
			}
		}
		between_centrality[i] = up / down ;
	}
	initstack(st);
	insertstack(st, between_centrality[0]);
	int pos = 0;
	for (int j = 1;j < sn.usernum;j++)
	{
		if (between_centrality[j] > st.a[st.top])
		{
			pos = j;
			//deletstack(st);
			insertstack(st, between_centrality[j]);
		}
	}
	cout << "�ؼ����between_centrality��IDΪ" << sn.ID[pos] << "���û�" << endl;
	for (int i = 0;i < sn.usernum;i++)
	{
		cout << between_centrality[i] << "  ";
	}
}

int main()
{
	//srand(time(0));
	Social_Networking sn;
	HashTable hash;
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
			inithash(&hash, sn.usernum);
			inithashinfo(sn, &hash);
			break;
		case 2:
			cout << "��������Ҫչʾ���û�ID" << endl;
			cin >> id;
			while (!idtest(sn, id))
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
			while (!idtest(sn, id))
			{
				cout << "id�����������������" << endl;
				cin >> id;
			}
			showhashinfo(&hash, id);
			friendlist(sn, id);
			cout << endl;
			cout << "��������ֵ����" << endl;
			cin >> a;
			break;
		case 5:
			cout << "�������û�ID" << endl;
			cin >> id;
			while (!idtest(sn, id))
			{
				cout << "id�����������������" << endl;
				cin >> id;
			}
			fri(sn, id);
			cout << "��������ֵ����" << endl;
			cin >> a;
			break;
		case 6:
			/*initvisited(sn);
			cout << "�����е�Ȧ�ӵĸ���Ϊ:" << endl;
			cout << analysecircl(sn) << "��" << endl;*/
			closeness_centrality(sn);
			degree_centrality(sn);
			between_centrality(sn);
			printNet(sn);
			cout << "��������ֵ����" << endl;
			cin >> a;
			break;
		case 7:
			cout << analysecircl(sn) << endl;
			cin >> a;
			break;
		default:
			cout << "��������" << endl;
			break;
		}
		system("cls");
	} while (choose != 8);
}