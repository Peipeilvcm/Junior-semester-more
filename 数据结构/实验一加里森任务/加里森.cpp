/*
����ɭ������
��n������ɭ�����ӵĶ�ԱҪը�����˵�һ������⣬˭������ȥ��
�ӳ�����ɭ�������ֻ������İ취�������ĸ�սʿȥִ�����񡣹������£�
���ǰһ��սʿû���������Ҫ����һ��սʿ��ȥ���ָ�ÿ��սʿ��һ���ţ�
���Χ����һȦ������ĳһ�����Ϊx��սʿ��ʼ������������yʱ��
��Ӧ��սʿ��ȥִ�������Ҵ�սʿ���ٲμ���һ�ּ����������սʿû�������
�ٴ���һ��սʿ��ʼ��������������yʱ����սʿ����ȥִ������
�Դ����ƣ�ֱ���������Ϊֹ��
����ɭ�����ǲ�Ը��ȥ�ģ��������ɭΪ1�ţ��������һ����Ϊ����ɭ֧�У�
���n,x,y�����������ʱ,����ɭ��������������ȥִ������;��
Ҫ��
��Ҫ���ݽṹ������ʽ�ṹ�洢��
����1��ʵ��ʵ����֤������ȷ�ԣ�����n,x,y���⣩��
*/
#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct s //ÿ���˵��������� 
{
	bool go;//�Ƿ�����������Ϊ0����Ϊ1 
	struct s *pnxt;
}node,*pnode;

pnode Create(pnode phead,int n)//��������ѭ������ 
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

bool Judge(pnode phead,int begin,int num)//�ж��Ƿ���к��� 
{
	pnode pcur = NULL, pts = phead->pnxt;
	int i = 1, live = 1;
	pcur = phead->pnxt;
	while(pcur != phead)//ͳ�������� 
	{
		live++;
		pcur = pcur->pnxt; 
	}
	while(begin != i++)//ָ��ʼ���� 
	{
		pcur = pcur->pnxt;
	}
	while(1)//��ʼ�ж� 
	{
		i = 1;
		if(1 == live)//��ʣһ������� 
		{
			return 1;
		}
		while(1)
		{
			if(i++ == num)
			{
				if(phead == pcur)//����ɭ��ѡ������� 
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

pnode Initialize(pnode phead)//��ʼ�������� 
{
	pnode pcur = phead->pnxt;
	while(pcur != phead)
	{
		pcur->go = 0;
		pcur = pcur->pnxt;
	}
	return phead;
}

pnode List(pnode phead,int n)//���Զ��ֿ��� 
{
	int i = 1, j = 1, x = 0;
	for(i = 1; i <= n; i++)
	{
		for(j = 1; j <= n; j++)
		{
			phead = Initialize(phead);
			if(1 == Judge(phead,i,j))//������������ 
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
	cout << "Please input the number of soldiers:" << endl;//����n 
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
	p = Create(p,n);//�������� 
	List(p,n);//�жϲ���� 
	system("pause");
	
	return 0;
}
