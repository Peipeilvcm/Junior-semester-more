#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<memory.h>
/*
先遍历，在该有向无环图中寻找入度为0的节点并在bool数组中表示为True,bool数组初始化为全True
再用递归的方式寻找每种路径的最后一个节点并计算路径长度
在带权有向无环图中寻找距离最远的两个点，起始节点入度必为0，结束节点出度必为0
*/
#define MAX_VERTEX_NUM 20
#define InfoType int
#define VertexType int
using namespace std;


typedef struct ArcNode {
	int adjvex;//该弧指向的顶点位置
	struct ArcNode *nextarc;//指向下一条弧的指针
	InfoType info;//原来是该弧相关信息的指针，这里改为一个int型变量表示该弧的权值
}ArcNode;
typedef struct VNode{
	VertexType data;//顶点信息
	ArcNode *firstarc;//指向第一条依附于该顶点的弧的指针
}VNode;
typedef struct {
	VNode AdjList[MAX_VERTEX_NUM];//顶点数组
	int vexnum,arcnum;//图的当前顶点数和弧数
	int kind;//图的种类标志
}ALGraph;


void isHead (int n,VNode l[],bool *b);//寻找入度为0的节点
void findFurthest(VNode l[],int x,int prelen,int *head,int *tail,int *maxlen,int ifHead);
/*寻找最长路径，l顶点数组，x当前节点在数组中的位置，prelen在到达此节点之前累计走
过的路径长度，tail最长路径尾节点所在位置，maxlen最长路径,ifhead储存当前正在计算
的路径的起始节点，注意此处head，tail，ifhead都是节点在数组中的位置，输出时数值需要+1s ←v ←*/


/*↓↓↓以下是函数主体↓↓↓*/
void WhatAMess (ALGraph	G, int *HV, int *TV){//通过返回节点在数组中位置的方式返回距离最远的两个点，HV,TV均初始化为0
	bool Vb[G.vexnum];//建立代表图中每个顶点能否作为起始顶点的布尔数组
	int  prelen=0,maxlen=0;
	int i;
	for(i=0;i<G.vexnum;i++){//将布尔型数组初始化为全true
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
			*(b+p->adjvex)=false;//将入度不为0的数组的对应的布尔变量置为false
			p=p->nextarc;
		}
	}
}

void findFurthest(VNode l[],int x,int prelen,int *head,int *tail,int *maxlen,int ifHead){
	ArcNode *p;
	if(l[x].firstarc==NULL){//若此时指向的节点出度为0，将累计的路径长度与maxlen比较，决定是否要修改
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

void InputGraph (ALGraph &G){//输入图，以邻接表形式
	int i,j;
	int num;
	int vn;
	ArcNode *p;
	cout<<"请输入有向无环图的节点个数（不超过20）"<<endl;
	cin>>G.vexnum;
	cout<<"接下来请输入每个节点上弧的信息"<<endl;
	for(i=0;i<G.vexnum;i++){
		G.AdjList[i].data=i+1;
		cout<<"请输入以节点"<<i+1<<"为尾节点的弧的条数"<<endl;
		cin>>num;
		if(num==0){
			G.AdjList[i].firstarc=NULL;
		}
		else{
			G.AdjList[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
			cout<<"请输入第1条弧指向的顶点"<<endl;
			cin>>vn;
			p=G.AdjList[i].firstarc;
			p->adjvex=vn-1;
			cout<<"请输入该弧的权值"<<endl;
			cin>>p->info;
			for(j=1;j<num;j++){
				p->nextarc=(ArcNode*)malloc(sizeof(ArcNode));
				p=p->nextarc;
				cout<<"请输入第"<<j+1<<"条弧指向的顶点"<<endl;
				cin>>vn;
				p->adjvex=vn-1;
				cout<<"请输入该弧的权值"<<endl;
				cin>>p->info;
			}
			p->nextarc=NULL;
		}
	}
	cout<<"感谢输入么么哒=333=~" <<endl;
}

int main (void){
	ALGraph G;
	int H=0,T=0;
	InputGraph(G);
	WhatAMess(G,&H,&T);
	cout<<"距离最远的两个点是点"<<H+1<<"和"<<T+1<<"。"<<endl;
	cout<<"感谢使用本程序:P"<<endl;
	return 0;
}
