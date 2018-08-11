#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100	//储存空间初始分配 
#define STACKINCREMENT 10//储存空间分配增量
#define OK 1
#define ERROR 0
#define Status int
#define QElemType char
#define SElemType char

typedef struct
{
	SElemType *base;//在栈构造之前和销毁后，base值为NULL 
	SElemType *top;//栈顶指针 
	int stacksize;//当前已分配的储存空间 
}SqStack;//栈的定义 

typedef struct QNode 
{
	QElemType data;
	struct QNode *next; 
}QNode,*QueuePtr;//队列的元素与指向元素的指针定义 
 
typedef struct
{
	QueuePtr front;//在栈构造之前和销毁后，front值为NULL 
	QueuePtr rear;//栈顶指针 
}LinkQueue;//队列的定义 

Status InitStack(SqStack &S)//构造空栈 
{
	S.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S.base)
	{
		printf("OVERFLOW");
		exit(0);
	}
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	return OK; 
}

Status DestroyStack(SqStack &S)//释放栈空间 
{
	if(S.base==NULL)//若栈不存在 
	{
		printf("ERROR");
		return ERROR;
	}
	
	free(S.base);
	S.base=NULL;
	S.top=NULL;
	S.stacksize=0;
	
	return OK;
}


Status StackFull(SqStack S)//判断栈满，为满返回1，否则返回0 
{	
	if(S.top-S.base==S.stacksize-1)
		return 1;
	else
		return 0;
}

Status Pop(SqStack &S,SElemType &e)
{//若栈不空，删除S栈顶元素，用e返回其值，并返回OK；否则返回ERROR 
	if(S.top==S.base)	return ERROR;
	e = *--S.top;
	return OK;
}

Status Push(SqStack &S,SElemType e)
{//插入元素e为新的栈顶元素 
	if(StackFull(S))//判断栈满 
	{
		printf("原栈已满，进行扩容\n");
		S.base=(SElemType*)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S.base)
		{
			printf("OVERFLOW");
			exit(0);
		}
		S.top=S.base+S.stacksize;
		S.stacksize+=STACKINCREMENT;
	}
	*S.top++ = e;
	
	return OK;
}

Status InitQueue(LinkQueue &Q)//构造空队列 
{
	Q.front=(QueuePtr)malloc(sizeof(QNode));
	Q.rear=Q.front;
	if(!Q.front)
	{
		printf("OVERFLOW");
		exit(0);
	}
	Q.front->next=NULL;
	return OK; 
}

Status DestroyQueue(LinkQueue &Q)
{//销毁队列Q
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	} 
	
	return OK;
}

Status EnQueue(LinkQueue &Q,QElemType e)
{//插入元素e为新的队尾元素
	QueuePtr p;
	p=(QueuePtr)malloc(sizeof(QNode));
	if(!p)
	{
		printf("OVERFLOW");
		exit(0);
	}
	p->data=e;	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;

	return OK;
}

Status DeQueue(LinkQueue &Q,QElemType &e)
{//若队列不空，删除Q的队头元素，用e返回其值，并返回OK；否则返回ERROR
	QueuePtr p;//临时指针 
	if(Q.front==Q.rear)	
		return ERROR;
	p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
		Q.rear=Q.front;
	free(p);

	return OK;
}

static int option=1;//操作选项变量
void menu()
{
	printf("请选择是否继续操作:(输入1为继续，0为退出)\n");
	scanf("%d",&option);
	fflush(stdin);//清除缓存区 
	if(option!=1&&option!=0)
	{
		printf("ERROR!!!\n请重新输入操作选项:(1为继续，0为退出)\n");
		scanf("%d",&option);
		fflush(stdin);
	}
}

void Input(SqStack &S,LinkQueue &Q)
{
	printf("请输入您要判别的的字符串:\n");		
	InitStack(S);
	InitQueue(Q);
	char e1,e2;
	scanf("%c",&e1);
	while(e1!='#')
	{
		Push(S,e1);
		EnQueue(Q,e1);
		scanf("%c",&e1);
	}
}

Status isSymmetry(SqStack S,LinkQueue Q)
{
	char e1,e2;
	while(S.top!=S.base||Q.rear!=Q.front)
	{
		Pop(S,e1);//栈做出站操作，先入后出 
		DeQueue(Q,e2);//队列做出队操作，先入先出 
		if(e1!=e2)
			return ERROR;

	}
	if(S.top==S.base&&Q.rear==Q.front)
		return OK;
	else
		return ERROR;
}

void Output(Status flag_)
{
	if(flag_)
		printf("YES，是的，它是回文字符串\n");
	else
		printf("NO，不，它不是回文字符串\n");
}


int main()
{
	Status flag;//flag为OK表示为回文字符串，ERROR表示不为 
	while(option)//option初始为1，之后输入操作选项，直至输入0退出 
	{
		SqStack S1;
		LinkQueue Q1;
		
		Input(S1,Q1);
		flag=isSymmetry(S1,Q1);
		Output(flag);
		
		DestroyStack(S1);	DestroyQueue(Q1);
		
		menu();
	}
	return 0;
}
