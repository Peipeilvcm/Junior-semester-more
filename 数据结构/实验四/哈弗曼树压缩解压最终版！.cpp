#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*将文件进行赫夫曼编码,以二进制位生产二进制文件(压缩文件)，可将压缩文件解码还原
 对选定的文件以二进制方式读入，一次读入一定的长度如1024 bytes，
 然后对每一字节（一字节8 bit，所以刚好对应256个ASCII字符）进行统计，如此循换统计
*/
typedef struct{
	unsigned long weight;
	unsigned int parent,lchild,rchild;
	unsigned char ch;
	char *Code;//动态分配数组储存赫夫曼编码表
}HTNode,*HuffmanTree;//动态分配数组储存赫夫曼树


typedef struct{
	unsigned long weight;
	unsigned char Ch;
}TNode;//临时储存统计文件的字符和其权值 

//全局变量 
HuffmanTree HufTree;//哈弗曼树与编码表
int char_kinds=0;//字符种类数
unsigned long file_len;//文件长度 

void Select(HuffmanTree ht,int n,int &a1,int &b1)
{//生成哈夫曼树需调用函数,在ht[0..n-1]的节点中找到权值最小的两个,用a1,b1返回 
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

int charCount(char *sourcefilename,TNode* &ChNode)//统计字符种类数与权值
{//统计文件中字符种类数与权值
	file_len=0;
	int i;
	ChNode=(TNode *)malloc(256*sizeof(TNode));
	//动态分配256个结点，储存字符和权值
	for(i=0;i<256;++i)
	{
		ChNode[i].Ch=(unsigned char)i;//确定256个字符的下标
		ChNode[i].weight=0;
	}

	FILE *fp;//二进制打开文件,用TNode数组记录
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
		
	return count;//返回统计不同字符个数 
}

int HuffmanCoding(HuffmanTree &HT,TNode *w)
{//w存放n个字符的权值，构造赫夫曼树HT
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
		{//初始化前ht[0...char_kinds-1]char_kingds个结点的信息 
			p->ch=w[j].Ch;
			p->lchild=0;p->parent=0;p->rchild=0;
			p->weight=w[j].weight;
			++p;++i;
		}

	for(;i<m;++i,++p)	*p={0,0,0,0,0};//初始化其余树节点 
	for(i=char_kinds;i<m;++i)
	{//建赫夫曼树
	//在HT[0..i-1]选择parent为0且weight最小的两个节点，其序号分别为是s1和s2
		Select(HT,i,s1,s2); 
		HT[s1].parent=i;HT[s2].parent=i;
		HT[i].lchild=s1;HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}

	//从叶子到根逆向求每个字符的赫夫曼编码
	char *cd;
	cd=(char*)malloc(char_kinds*sizeof(char));//分配求编码空间
	cd[char_kinds-1]='\0';//编码结束符

	int start,c,f;
	for(i=0;i<char_kinds;i++)
	{//逐个字符求赫夫曼编码
		start=char_kinds-1;//编码结束位置
		for(c=i,f=HT[i].parent; f!=0; c=f,f=HT[f].parent)
		{//从叶子到根逆向求编码
			if(HT[f].lchild==c)	cd[--start]='0';
			else	cd[--start]='1';
		}
		HT[i].Code=(char*)malloc((char_kinds-start)*sizeof(char));//为第i个字符编码分配空间
		strcpy(HT[i].Code,&cd[start]);//从sd复制编码到HT[i]中的哈夫曼编码中 
	}
	free(cd);//释放工作空间
	printf("成功创建哈弗曼树并编码\n");
/*	printf("一共%d个不同的字符\n",char_kinds);//打印哈弗曼树信息,可不要 
	for(i=0;i<char_kinds;i++)
	{
		printf("字符%c\t",(unsigned char)HufTree[i].ch);//打印哈夫曼编码表
		printf("权值%d\t哈夫曼编码为%s\n",HufTree[i].weight,HufTree[i].Code);
	}*/
	return 1;
}

void Compress(char *sourcefilename,char *outfilename)
{//压缩函数,需要压缩的文件与压缩后输出的文件 
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
	//动态分配256个结点，储存字符和权值
	char_kinds=charCount(sourcefilename,chNode);//统计字符
	
	if(char_kinds==1)
	{//特殊情况处理 
		for(i=0;i<256;i++)
			if(chNode[i].weight!=0)
				break;
		fwrite((unsigned char *)&chNode[i].Ch,sizeof(unsigned char),1,fptr2);
		free(chNode);//释放chNode空间
		fclose(fptr2);
		return;
	}
	
	HuffmanCoding(HufTree,chNode);
	//生成哈弗曼树与哈夫曼编码
	free(chNode);//释放chNode空间
	 
	unsigned char temp=0;
	char CodeBuf[100]={'\0'};
						
	fread((unsigned char *)&temp,sizeof(unsigned char),1,fptr);
	while(!feof(fptr))
	{//找到字符对应哈夫曼编码
		for(i=0;i<char_kinds;++i)
			if((unsigned char)temp==HufTree[i].ch)
				strcat(CodeBuf,HufTree[i].Code);	
		while(strlen(CodeBuf)>=8)
		{
			temp='\0';
			for(i=0;i<8;++i)//将CodeBuf中前8位变为相应ASCII码
			{
				temp <<= 1;//左移一位
				if(CodeBuf[i]=='1')
					temp |= 1;//取或运算
			}
			fwrite((unsigned char *)&temp,sizeof(unsigned char),1,fptr2);
			//将转化后的ASCII码输入outfile中
			strcpy(CodeBuf,CodeBuf+8);//清除已转化的前8位
		}
		
		fread((unsigned char *)&temp,sizeof(unsigned char),1,fptr);
	}
	//处理最后不足8位情况
	int last_clen=strlen(CodeBuf);//最后二进制长度
	if(last_clen>0)
	{
		temp='\0';
		for(i=0;i<last_clen;++i)//将CodeBuf中前8位变为相应ASCII码
		{
			temp <<= 1;//左移一位
			if(CodeBuf[i]=='1')
				temp |= 1;//取或运算
		}
		temp <<= 8-last_clen;
		fwrite((unsigned char *)&temp,sizeof(unsigned char),1,fptr2);
	}
	
	printf("成功将%s压缩至%s\n",sourcefilename,outfilename); 
	fclose(fptr);//关闭文件 
	fclose(fptr2); 
}

void UnCompress(char *sourcefilename,char *outfilename)
{//解压函数,待解压文件和解压后输出文件 
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
		//读取一个字符
		for(i=0;i<8;i++) 
		{//由根向下直至叶节点正向匹配编码对应字符
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
			temp <<= 1;//左移一位，以供匹配 
		}
		
		if((write_len*20)/file_len > flag){printf("*");flag++;
		}
		if(write_len==file_len)	break;
	}
	printf("\n成功将%s解压至%s\n",sourcefilename,outfilename);
	fclose(fptr);//关闭文件 
	fclose(fptr2);
}

int main()
{
	char sourcefilename[20],outfilename[20];
	int choice;
	printf("请选择您的操作:	输入1压缩,输入2解压,输入0退出\n");
	scanf("%d",&choice);
	while(choice)
	{
		switch(choice)
		{
			case 1:
				printf("请输入源文件名与输出文件名,空格隔开:\n");
				scanf("%s %s",&sourcefilename,&outfilename);
				Compress(sourcefilename,outfilename);
				break;
			case 2:
				printf("请输入源文件名与输出文件名,空格隔开:\n");
				scanf("%s %s",&sourcefilename,&outfilename);
				UnCompress(sourcefilename,outfilename);
				break;
			default:
				printf("输入错误\n");	break;
		}
		printf("请选择您的操作:	输入1压缩,输入2解压,输入0退出\n");
		scanf("%d",&choice);
	}
	
	system("pause");
	return 0;
}


