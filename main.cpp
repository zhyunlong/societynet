#include "head.h"
#include <iostream>
#include <time.h>

using namespace std;

void initnet(Social_Networking & SN)
{
	SN.arcnum = 0;
	SN.usernum = 0;
	cout << "请输入网络中用户数量" << endl;
	cin >> SN.usernum;
	for (int i = 0;i < MAX;i++)
	{
		SN.ID[i] = -1;
	}
	for (int i = 0;i < MAX;i++)
	{
		for (int j = 0;i < MAX;j++)
		{
			SN.net[i][j] = 0;//0表示无好友关系
		}//在图中存储信息 以后再构造哈希表 用来查找
	}
}


void buildNet(Social_Networking &SN)
{
	//为每个用户生成唯一的ID号（四位纯数字）
	for (int i = 0;i < SN.usernum;i++)
	{
		SN.ID[i] = rand() % 1000000;
		for (int j = 0;j < i;j++)
		{
			if (SN.ID[i] == SN.ID[j])
			{
				j = 0;
				SN.ID[i] = rand() % 10000;
			}
		}
	}
	for (int i = 0;i < SN.usernum;i++)
	{
		for (int j = 0;j < SN.usernum;j++)
		{
			if (rand() % 2 == 0)
				SN.net[i][j] = 1;
			else
				SN.net[i][j] = 0;
		}
	}
}

int main()
{
	Social_Networking sn;
	cout<<sn.arcnum;

}