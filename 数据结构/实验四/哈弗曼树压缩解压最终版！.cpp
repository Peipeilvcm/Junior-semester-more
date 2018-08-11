#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*���ļ����кշ�������,�Զ�����λ�����������ļ�(ѹ���ļ�)���ɽ�ѹ���ļ����뻹ԭ
 ��ѡ�����ļ��Զ����Ʒ�ʽ���룬һ�ζ���һ���ĳ�����1024 bytes��
 Ȼ���ÿһ�ֽڣ�һ�ֽ�8 bit�����Ըպö�Ӧ256��ASCII�ַ�������ͳ�ƣ����ѭ��ͳ��
*/
typedef struct{
	unsigned long weight;
	unsigned int parent,lchild,rchild;
	unsigned char ch;
	char *Code;//��̬�������鴢��շ��������
}HTNode,*HuffmanTree;//��̬�������鴢��շ�����


typedef struct{
	unsigned long weight;
	unsigned char Ch;
}TNode;//��ʱ����ͳ���ļ����ַ�����Ȩֵ 

//ȫ�ֱ��� 
HuffmanTree HufTree;//��������������
int char_kinds=0;//�ַ�������
unsigned long file_len;//�ļ����� 

void Select(HuffmanTree ht,int n,int &a1,int &b1)
{//���ɹ�����������ú���,��ht[0..n-1]�Ľڵ����ҵ�Ȩֵ��С������,��a1,b1���� 
	int i;
	for(i=0;i<n;i++)
	{
		if(ht[i].parent==0)
		{
			a1=i;
			break;
		}
	}
	for(i=0;i<n;i++)
	{
		if(i==a1)	continue;
		if(ht[i].parent==0)
		{
			b1=i;
			break;
		}
	}
	for(i=0;i<n;i++)
		if(ht[i].parent==0&&ht[a1].weight>ht[i].weight)
		{
			b1=a1;
			a1=i;
		}
	for(i=0;i<n;i++)
	{
		if(i==a1)	continue;
		if(ht[i].parent==0&&ht[b1].weight>ht[i].weight)
			b1=i;
	}
}

int charCount(char *sourcefilename,TNode* &ChNode)//ͳ���ַ���������Ȩֵ
{//ͳ���ļ����ַ���������Ȩֵ
	file_len=0;
	int i;
	ChNode=(TNode *)malloc(256*sizeof(TNode));
	//��̬����256����㣬�����ַ���Ȩֵ
	for(i=0;i<256;++i)
	{
		ChNode[i].Ch=(unsigned char)i;//ȷ��256���ַ����±�
		ChNode[i].weight=0;
	}

	FILE *fp;//�����ƴ��ļ�,��TNode�����¼
	if((fp=fopen(sourcefilename,"rb"))==NULL)
	{
		printf("can't open the source file\n");
		return 0;
	}

	unsigned char temp;
	fread((unsigned char *)&temp,sizeof(unsigned char),1,fp);
	while(!feof(fp))
	{
		++ChNode[temp].weight;
		++file_len;
		fread((unsigned char *)&temp,sizeof(unsigned char),1,fp);
	}
	fclose(fp);

	int count=0;
	for(i=0;i<256;++i)
		if(ChNode[i].weight!=0)
			++count;
		
	return count;//����ͳ�Ʋ�ͬ�ַ����� 
}

int HuffmanCoding(HuffmanTree &HT,TNode *w)
{//w���n���ַ���Ȩֵ������շ�����HT
	if(char_kinds<=1)	return 0;
	int i=0;
	int m;
	int s1,s2;
	HuffmanTree p;
	m=2*char_kinds-1;
	HT=(HuffmanTree)malloc((m)*sizeof(HTNode));
	
	int j=0;
	p=HT;
	for(j=0;j<256;++j)
		if(w[j].weight!=0)
		{//��ʼ��ǰht[0...char_kinds-1]char_kingds��������Ϣ 
			p->ch=w[j].Ch;
			p->lchild=0;p->parent=0;p->rchild=0;
			p->weight=w[j].weight;
			++p;++i;
		}

	for(;i<m;++i,++p)	*p={0,0,0,0,0};//��ʼ���������ڵ� 
	for(i=char_kinds;i<m;++i)
	{//���շ�����
	//��HT[0..i-1]ѡ��parentΪ0��weight��С�������ڵ㣬����ŷֱ�Ϊ��s1��s2
		Select(HT,i,s1,s2); 
		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}

	//��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
	char *cd;
	cd=(char*)malloc(char_kinds*sizeof(char));//���������ռ�
	cd[char_kinds-1]='\0';//���������

	int start,c,f;
	for(i=0;i<char_kinds;i++)
	{//����ַ���շ�������
		start=char_kinds-1;//�������λ��
		for(c=i,f=HT[i].parent; f!=0; c=f,f=HT[f].parent)
		{//��Ҷ�ӵ������������
			if(HT[f].lchild==c)	cd[--start]='0';
			else	cd[--start]='1';
		}
		HT[i].Code=(char*)malloc((char_kinds-start)*sizeof(char));//Ϊ��i���ַ��������ռ�
		strcpy(HT[i].Code,&cd[start]);//��sd���Ʊ��뵽HT[i]�еĹ����������� 
	}
	free(cd);//�ͷŹ����ռ�
	printf("�ɹ�������������������\n");
/*	printf("һ��%d����ͬ���ַ�\n",char_kinds);//��ӡ����������Ϣ,�ɲ�Ҫ 
	for(i=0;i<char_kinds;i++)
	{
		printf("�ַ�%c\t",(unsigned char)HufTree[i].ch);//��ӡ�����������
		printf("Ȩֵ%d\t����������Ϊ%s\n",HufTree[i].weight,HufTree[i].Code);
	}*/
	return 1;
}

void Compress(char *sourcefilename,char *outfilename)
{//ѹ������,��Ҫѹ�����ļ���ѹ����������ļ� 
	FILE *fptr,*fptr2;
	TNode *chNode;
	if((fptr=fopen(sourcefilename,"rb"))==NULL)
	{
		printf("can't open the source file\n");
		return;
	}
	if((fptr2=fopen(outfilename,"wb"))==NULL)
	{
		printf("can't open the output file\n");
		return;
	}
	
	int i;
	//��̬����256����㣬�����ַ���Ȩֵ
	char_kinds=charCount(sourcefilename,chNode);//ͳ���ַ�
	
	if(char_kinds==1)
	{//����������� 
		for(i=0;i<256;i++)
			if(chNode[i].weight!=0)
				break;
		fwrite((unsigned char *)&chNode[i].Ch,sizeof(unsigned char),1,fptr2);
		free(chNode);//�ͷ�chNode�ռ�
		fclose(fptr2);
		return;
	}
	
	HuffmanCoding(HufTree,chNode);
	//���ɹ������������������
	free(chNode);//�ͷ�chNode�ռ�
	 
	unsigned char temp=0;
	char CodeBuf[100]={'\0'};
						
	fread((unsigned char *)&temp,sizeof(unsigned char),1,fptr);
	while(!feof(fptr))
	{//�ҵ��ַ���Ӧ����������
		for(i=0;i<char_kinds;++i)
			if((unsigned char)temp==HufTree[i].ch)
				strcat(CodeBuf,HufTree[i].Code);	
		while(strlen(CodeBuf)>=8)
		{
			temp='\0';
			for(i=0;i<8;++i)//��CodeBuf��ǰ8λ��Ϊ��ӦASCII��
			{
				temp <<= 1;//����һλ
				if(CodeBuf[i]=='1')
					temp |= 1;//ȡ������
			}
			fwrite((unsigned char *)&temp,sizeof(unsigned char),1,fptr2);
			//��ת�����ASCII������outfile��
			strcpy(CodeBuf,CodeBuf+8);//�����ת����ǰ8λ
		}
		
		fread((unsigned char *)&temp,sizeof(unsigned char),1,fptr);
	}
	//���������8λ���
	int last_clen=strlen(CodeBuf);//�������Ƴ���
	if(last_clen>0)
	{
		temp='\0';
		for(i=0;i<last_clen;++i)//��CodeBuf��ǰ8λ��Ϊ��ӦASCII��
		{
			temp <<= 1;//����һλ
			if(CodeBuf[i]=='1')
				temp |= 1;//ȡ������
		}
		temp <<= 8-last_clen;
		fwrite((unsigned char *)&temp,sizeof(unsigned char),1,fptr2);
	}
	
	printf("�ɹ���%sѹ����%s\n",sourcefilename,outfilename); 
	fclose(fptr);//�ر��ļ� 
	fclose(fptr2); 
}

void UnCompress(char *sourcefilename,char *outfilename)
{//��ѹ����,����ѹ�ļ��ͽ�ѹ������ļ� 
	unsigned long write_len=0;
	FILE *fptr,*fptr2;
	if((fptr=fopen(sourcefilename,"rb"))==NULL)
		printf("can't open the source file\n");
	if((fptr2=fopen(outfilename,"wb"))==NULL)
		printf("can't open the output file\n");
	
	unsigned char temp=0;
	int i;
	if(char_kinds==1)
	{
		fread((unsigned char *)&temp,sizeof(unsigned char),1,fptr);
		while(file_len--)
			fwrite((unsigned char *)&temp,sizeof(unsigned char),1,fptr2);
		fclose(fptr);
		fclose(fptr2);
		return;
	}
	int flag = 1;
	unsigned int root = 2*char_kinds-2;
	while(1)
	{
		fread((unsigned char *)&temp,sizeof(unsigned char),1,fptr);
		//��ȡһ���ַ�
		for(i=0;i<8;i++) 
		{//�ɸ�����ֱ��Ҷ�ڵ�����ƥ������Ӧ�ַ�
			if(temp&128)
				root = HufTree[root].rchild;
			else
				root = HufTree[root].lchild;
								
			if(root<char_kinds)
			{
				fwrite((unsigned char *)&HufTree[root].ch,sizeof(unsigned char),1,fptr2);
				++write_len;
				if(write_len==file_len)	break;
				root = 2*char_kinds-2;
			}
			temp <<= 1;//����һλ���Թ�ƥ�� 
		}
		
		if((write_len*20)/file_len > flag){printf("*");flag++;
		}
		if(write_len==file_len)	break;
	}
	printf("\n�ɹ���%s��ѹ��%s\n",sourcefilename,outfilename);
	fclose(fptr);//�ر��ļ� 
	fclose(fptr2);
}

int main()
{
	char sourcefilename[20],outfilename[20];
	int choice;
	printf("��ѡ�����Ĳ���:	����1ѹ��,����2��ѹ,����0�˳�\n");
	scanf("%d",&choice);
	while(choice)
	{
		switch(choice)
		{
			case 1:
				printf("������Դ�ļ���������ļ���,�ո����:\n");
				scanf("%s %s",&sourcefilename,&outfilename);
				Compress(sourcefilename,outfilename);
				break;
			case 2:
				printf("������Դ�ļ���������ļ���,�ո����:\n");
				scanf("%s %s",&sourcefilename,&outfilename);
				UnCompress(sourcefilename,outfilename);
				break;
			default:
				printf("�������\n");	break;
		}
		printf("��ѡ�����Ĳ���:	����1ѹ��,����2��ѹ,����0�˳�\n");
		scanf("%d",&choice);
	}
	
	system("pause");
	return 0;
}


