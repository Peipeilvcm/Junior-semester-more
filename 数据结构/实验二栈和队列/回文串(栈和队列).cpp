#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_SIZE 100	//����ռ��ʼ���� 
#define STACKINCREMENT 10//����ռ��������
#define OK 1
#define ERROR 0
#define Status int
#define QElemType char
#define SElemType char

typedef struct
{
	SElemType *base;//��ջ����֮ǰ�����ٺ�baseֵΪNULL 
	SElemType *top;//ջ��ָ�� 
	int stacksize;//��ǰ�ѷ���Ĵ���ռ� 
}SqStack;//ջ�Ķ��� 

typedef struct QNode 
{
	QElemType data;
	struct QNode *next; 
}QNode,*QueuePtr;//���е�Ԫ����ָ��Ԫ�ص�ָ�붨�� 
 
typedef struct
{
	QueuePtr front;//��ջ����֮ǰ�����ٺ�frontֵΪNULL 
	QueuePtr rear;//ջ��ָ�� 
}LinkQueue;//���еĶ��� 

Status InitStack(SqStack &S)//�����ջ 
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

Status DestroyStack(SqStack &S)//�ͷ�ջ�ռ� 
{
	if(S.base==NULL)//��ջ������ 
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


Status StackFull(SqStack S)//�ж�ջ����Ϊ������1�����򷵻�0 
{	
	if(S.top-S.base==S.stacksize-1)
		return 1;
	else
		return 0;
}

Status Pop(SqStack &S,SElemType &e)
{//��ջ���գ�ɾ��Sջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR 
	if(S.top==S.base)	return ERROR;
	e = *--S.top;
	return OK;
}

Status Push(SqStack &S,SElemType e)
{//����Ԫ��eΪ�µ�ջ��Ԫ�� 
	if(StackFull(S))//�ж�ջ�� 
	{
		printf("ԭջ��������������\n");
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

Status InitQueue(LinkQueue &Q)//����ն��� 
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
{//���ٶ���Q
	while(Q.front)
	{
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	} 
	
	return OK;
}

Status EnQueue(LinkQueue &Q,QElemType e)
{//����Ԫ��eΪ�µĶ�βԪ��
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
{//�����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR
	QueuePtr p;//��ʱָ�� 
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

static int option=1;//����ѡ�����
void menu()
{
	printf("��ѡ���Ƿ��������:(����1Ϊ������0Ϊ�˳�)\n");
	scanf("%d",&option);
	fflush(stdin);//��������� 
	if(option!=1&&option!=0)
	{
		printf("ERROR!!!\n�������������ѡ��:(1Ϊ������0Ϊ�˳�)\n");
		scanf("%d",&option);
		fflush(stdin);
	}
}

void Input(SqStack &S,LinkQueue &Q)
{
	printf("��������Ҫ�б�ĵ��ַ���:\n");		
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
		Pop(S,e1);//ջ����վ������������ 
		DeQueue(Q,e2);//���������Ӳ����������ȳ� 
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
		printf("YES���ǵģ����ǻ����ַ���\n");
	else
		printf("NO�����������ǻ����ַ���\n");
}


int main()
{
	Status flag;//flagΪOK��ʾΪ�����ַ�����ERROR��ʾ��Ϊ 
	while(option)//option��ʼΪ1��֮���������ѡ�ֱ������0�˳� 
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
