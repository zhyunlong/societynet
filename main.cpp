#include "head.h"
#include <time.h>
#include <iostream>
#include <iomanip>
#include <algorithm>


#define INFINITY  65535

using namespace std;


int final[MAX][MAX], path[MAX][MAX] = {-1};

//利用哈希表存储用户信息 ID作为主关键字是不会重复的 对ID利用哈希函数处理

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
		cout << "用户" << i + 1 << ": " << SN.ID[i];
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
	}//获取其下标
	for (int j = 0;j < SN.usernum;j++)
	{
		if (SN.net[i][j] != INFINITY&&SN.net[i][j] != 0)
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
		if (SN.net[i][j] != INFINITY&&SN.net[i][j] != 0)
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
	cout << "任意两点间最短距离: " << endl;
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
	cout << "关键人物（degree）ID为" << sn.ID[pos] << "的用户" << endl;
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
	cout << "关键人物（closeness_centrality）ID为" << sn.ID[pos] << "的用户" <<st.a[st.top] << endl;
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
	cout << "关键人物（between_centrality）ID为" << sn.ID[pos] << "的用户" << endl;
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
			inithash(&hash, sn.usernum);
			inithashinfo(sn, &hash);
			break;
		case 2:
			cout << "请输入想要展示的用户ID" << endl;
			cin >> id;
			while (!idtest(sn, id))
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
			while (!idtest(sn, id))
			{
				cout << "id输入错误，请重新输入" << endl;
				cin >> id;
			}
			showhashinfo(&hash, id);
			friendlist(sn, id);
			cout << endl;
			cout << "输入任意值返回" << endl;
			cin >> a;
			break;
		case 5:
			cout << "请输入用户ID" << endl;
			cin >> id;
			while (!idtest(sn, id))
			{
				cout << "id输入错误，请重新输入" << endl;
				cin >> id;
			}
			fri(sn, id);
			cout << "输入任意值返回" << endl;
			cin >> a;
			break;
		case 6:
			/*initvisited(sn);
			cout << "网络中的圈子的个数为:" << endl;
			cout << analysecircl(sn) << "个" << endl;*/
			closeness_centrality(sn);
			degree_centrality(sn);
			between_centrality(sn);
			printNet(sn);
			cout << "输入任意值返回" << endl;
			cin >> a;
			break;
		case 7:
			cout << analysecircl(sn) << endl;
			cin >> a;
			break;
		default:
			cout << "输入有误" << endl;
			break;
		}
		system("cls");
	} while (choose != 8);
}