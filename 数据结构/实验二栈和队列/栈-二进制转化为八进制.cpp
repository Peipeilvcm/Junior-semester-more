#include <iostream>
#include <math.h>
using namespace std;

struct Elem{
	char data;
	Elem *next;
};
class STK {//����һ��ջ 
	private:
		Elem *top;
	public:
		STK(){ 
			top=new Elem; 
			top->next=NULL; 
		} ;
		void Push(char i); 
    	char Pop(); 
    	bool IsEmpty(); 
};

void STK::Push(char i) //ͷ�巨
{  
    Elem *p; 
    p=new Elem; 
    p->data=i; 
    p->next=top->next; 
    top->next=p; 
} 
char STK::Pop() //ɾ��������ջ��Ԫ�� 
{ 
    Elem *p; 
    char x; 
    x=top->next->data; 
    p=top->next; 
    top->next=top->next->next; 
    delete p; 
    return x; 
} 
bool STK::IsEmpty() //��ջ�Ƿ�Ϊ�� 
{ 
    return (top->next==NULL); 
} 
void trans (STK &s,STK &y){//������ת��Ϊ8���� 
	int i=0,ad=0;
	while(!(s.IsEmpty())){
		ad=ad+(s.Pop()-48)*1;
		if(!(s.IsEmpty())){
			ad=ad+(s.Pop()-48)*2;
			if(!(s.IsEmpty())){
				ad=ad+(s.Pop()-48)*4;
			}
		}
		y.Push(ad+48);
		ad=0; 
	}
} 
int sets (STK &s){//����������ַ��� 
	char c; 
	scanf("%c",&c);
	while(c!='#'){///������Ķ���������ջ����ʽ���� 
		s.Push(c);
		scanf("%c",&c);
	} 
} 
int main (void){
	STK s,y;
	char c;
	int ad;
	cout<<"�������������(��#����)��"<<endl;
	sets(s);
	trans(s,y);
	cout<<"ת��Ϊ�˽��ƵĽ���ǣ�"; 
	while(!(y.IsEmpty())){
		cout<<y.Pop();
	}
	return 0;
}
