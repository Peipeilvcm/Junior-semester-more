/*
加里森的任务
有n个加里森敢死队的队员要炸掉敌人的一个军火库，谁都不想去，
队长加里森决定用轮回数数的办法来决定哪个战士去执行任务。规则如下：
如果前一个战士没完成任务，则要再派一个战士上去。现给每个战士编一个号，
大家围坐成一圈，随便从某一个编号为x的战士开始计数，当数到y时，
对应的战士就去执行任务，且此战士不再参加下一轮计数。如果此战士没完成任务，
再从下一个战士开始数数，被数到第y时，此战士接着去执行任务。
以此类推，直到任务完成为止。
加里森本人是不愿意去的，假设加里森为1号，请你设计一程序为加里森支招，
求出n,x,y满足何种条件时,加里森能留到最后而不用去执行任务;。
要求：
主要数据结构采用链式结构存储。
自拟1个实验实例验证程序正确性（即：n,x,y自拟）。
*/
#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct s //每个人的数据类型 
{
	bool go;//是否已死，活着为0，死为1 
	struct s *pnxt;
}node,*pnode;

pnode Create(pnode phead,int n)//创建单向循环链表 
{
	int i = 1;
	pnode pcur = NULL, pts = NULL;
	phead = new node;
	phead->go = 0;
	pts = phead;
	while(1)
	{
		if(i++ == n)
		{
			pcur->pnxt = phead;
			return phead;
		}
		pcur = new node;
		pcur->go = 0;
		pts->pnxt = pcur;
		pts = pts->pnxt;
	}
}

bool Judge(pnode phead,int begin,int num)//判断是否可行函数 
{
	pnode pcur = NULL, pts = phead->pnxt;
	int i = 1, live = 1;
	pcur = phead->pnxt;
	while(pcur != phead)//统计总人数 
	{
		live++;
		pcur = pcur->pnxt; 
	}
	while(begin != i++)//指向开始的人 
	{
		pcur = pcur->pnxt;
	}
	while(1)//开始判断 
	{
		i = 1;
		if(1 == live)//仅剩一人则可行 
		{
			return 1;
		}
		while(1)
		{
			if(i++ == num)
			{
				if(phead == pcur)//哈里森被选中则结束 
				{
					return 0;
				}
				pcur->go = 1;
				pcur = pcur->pnxt;
				while(1 == pcur->go)
				{
					pcur = pcur->pnxt;
				}
				break;
			}
			
			pcur = pcur->pnxt;
			while(1 == pcur->go)
			{
				pcur = pcur->pnxt;
			}			
		}
		live--; 
	}
}

pnode Initialize(pnode phead)//初始化链表函数 
{
	pnode pcur = phead->pnxt;
	while(pcur != phead)
	{
		pcur->go = 0;
		pcur = pcur->pnxt;
	}
	return phead;
}

pnode List(pnode phead,int n)//尝试多种可能 
{
	int i = 1, j = 1, x = 0;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			phead = Initialize(phead);
			if(1 == Judge(phead,i,j))//如果可行则输出 
			{
				cout << "Begin from " << i << " , by " << j << " ." << endl;
				x++;
			}
		}
	}
	if(0 == x)
	{
		cout << "It seemed that Harrison had to go die 23333333." << endl;
	}
	return phead;
}


int main()
{
	pnode p = NULL;
	int n = 0, a = 1, b = 2;
	cout << "Please input the number of soldiers:" << endl;//输入n 
	cin >> n ;
	while(n<=0 || a<1 || b<1)
	{
		cout << "Error;Please input again:";
		cin >> n ;
		cout << endl;
	}
	if(1 == n)
	{
		cout << "It seemed that Harrison had to go die 23333333." << endl;
		return 0;
	}
	p = Create(p,n);//创建链表 
	List(p,n);//判断并输出 
	system("pause");
	
	return 0;
}
