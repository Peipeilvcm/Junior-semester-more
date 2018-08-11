#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<memory.h>
/*
�ȱ������ڸ������޻�ͼ��Ѱ�����Ϊ0�Ľڵ㲢��bool�����б�ʾΪTrue,bool�����ʼ��ΪȫTrue
���õݹ�ķ�ʽѰ��ÿ��·�������һ���ڵ㲢����·������
�ڴ�Ȩ�����޻�ͼ��Ѱ�Ҿ�����Զ�������㣬��ʼ�ڵ���ȱ�Ϊ0�������ڵ���ȱ�Ϊ0
*/
#define MAX_VERTEX_NUM 20
#define InfoType int
#define VertexType int
using namespace std;


typedef struct ArcNode {
	int adjvex;//�û�ָ��Ķ���λ��
	struct ArcNode *nextarc;//ָ����һ������ָ��
	InfoType info;//ԭ���Ǹû������Ϣ��ָ�룬�����Ϊһ��int�ͱ�����ʾ�û���Ȩֵ
}ArcNode;
typedef struct VNode{
	VertexType data;//������Ϣ
	ArcNode *firstarc;//ָ���һ�������ڸö���Ļ���ָ��
}VNode;
typedef struct {
	VNode AdjList[MAX_VERTEX_NUM];//��������
	int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ���
	int kind;//ͼ�������־
}ALGraph;


void isHead (int n,VNode l[],bool *b);//Ѱ�����Ϊ0�Ľڵ�
void findFurthest(VNode l[],int x,int prelen,int *head,int *tail,int *maxlen,int ifHead);
/*Ѱ���·����l�������飬x��ǰ�ڵ��������е�λ�ã�prelen�ڵ���˽ڵ�֮ǰ�ۼ���
����·�����ȣ�tail�·��β�ڵ�����λ�ã�maxlen�·��,ifhead���浱ǰ���ڼ���
��·������ʼ�ڵ㣬ע��˴�head��tail��ifhead���ǽڵ��������е�λ�ã����ʱ��ֵ��Ҫ+1s ��v ��*/


/*�����������Ǻ������������*/
void WhatAMess (ALGraph	G, int *HV, int *TV){//ͨ�����ؽڵ���������λ�õķ�ʽ���ؾ�����Զ�������㣬HV,TV����ʼ��Ϊ0
	bool Vb[G.vexnum];//��������ͼ��ÿ�������ܷ���Ϊ��ʼ����Ĳ�������
	int  prelen=0,maxlen=0;
	int i;
	for(i=0;i<G.vexnum;i++){//�������������ʼ��Ϊȫtrue
		Vb[i]=true;
	}
	isHead(G.vexnum,G.AdjList,Vb);
	for(i=0;i<G.vexnum;i++){
		if(Vb[i]){
			findFurthest(G.AdjList,i,prelen,HV,TV,&maxlen,i);
		}
	}
}

void isHead (int n,VNode l[],bool *b){
	ArcNode *p;
	for(int i=0;i<n;i++){
		p=l[i].firstarc;
		while(p!=NULL){
			*(b+p->adjvex)=false;//����Ȳ�Ϊ0������Ķ�Ӧ�Ĳ���������Ϊfalse
			p=p->nextarc;
		}
	}
}

void findFurthest(VNode l[],int x,int prelen,int *head,int *tail,int *maxlen,int ifHead){
	ArcNode *p;
	if(l[x].firstarc==NULL){//����ʱָ��Ľڵ����Ϊ0�����ۼƵ�·��������maxlen�Ƚϣ������Ƿ�Ҫ�޸�
		if(prelen>*maxlen){
			*maxlen=prelen;
			*tail=x;
			*head=ifHead;

		}
		else;
	}
	else{
		p=l[x].firstarc;
		while(p!=NULL){
			findFurthest(l,p->adjvex,prelen+(p->info),head,tail,maxlen,ifHead);
			p=p->nextarc;
		}
	}
}

void InputGraph (ALGraph &G){//����ͼ�����ڽӱ���ʽ
	int i,j;
	int num;
	int vn;
	ArcNode *p;
	cout<<"�����������޻�ͼ�Ľڵ������������20��"<<endl;
	cin>>G.vexnum;
	cout<<"������������ÿ���ڵ��ϻ�����Ϣ"<<endl;
	for(i=0;i<G.vexnum;i++){
		G.AdjList[i].data=i+1;
		cout<<"�������Խڵ�"<<i+1<<"Ϊβ�ڵ�Ļ�������"<<endl;
		cin>>num;
		if(num==0){
			G.AdjList[i].firstarc=NULL;
		}
		else{
			G.AdjList[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
			cout<<"�������1����ָ��Ķ���"<<endl;
			cin>>vn;
			p=G.AdjList[i].firstarc;
			p->adjvex=vn-1;
			cout<<"������û���Ȩֵ"<<endl;
			cin>>p->info;
			for(j=1;j<num;j++){
				p->nextarc=(ArcNode*)malloc(sizeof(ArcNode));
				p=p->nextarc;
				cout<<"�������"<<j+1<<"����ָ��Ķ���"<<endl;
				cin>>vn;
				p->adjvex=vn-1;
				cout<<"������û���Ȩֵ"<<endl;
				cin>>p->info;
			}
			p->nextarc=NULL;
		}
	}
	cout<<"��л����ôô��=333=~" <<endl;
}

int main (void){
	ALGraph G;
	int H=0,T=0;
	InputGraph(G);
	WhatAMess(G,&H,&T);
	cout<<"������Զ���������ǵ�"<<H+1<<"��"<<T+1<<"��"<<endl;
	cout<<"��лʹ�ñ�����:P"<<endl;
	return 0;
}
