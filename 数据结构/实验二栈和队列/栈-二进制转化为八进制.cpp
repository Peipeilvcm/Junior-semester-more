#include <iostream>
#include <math.h>
using namespace std;

struct Elem{
	char data;
	Elem *next;
};
class STK {//定义一个栈 
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

void STK::Push(char i) //头插法
{  
    Elem *p; 
    p=new Elem; 
    p->data=i; 
    p->next=top->next; 
    top->next=p; 
} 
char STK::Pop() //删除并返回栈顶元素 
{ 
    Elem *p; 
    char x; 
    x=top->next->data; 
    p=top->next; 
    top->next=top->next->next; 
    delete p; 
    return x; 
} 
bool STK::IsEmpty() //判栈是否为空 
{ 
    return (top->next==NULL); 
} 
void trans (STK &s,STK &y){//二进制转化为8进制 
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
int sets (STK &s){//输入二进制字符串 
	char c; 
	scanf("%c",&c);
	while(c!='#'){///把输入的二进制数以栈的形式储存 
		s.Push(c);
		scanf("%c",&c);
	} 
} 
int main (void){
	STK s,y;
	char c;
	int ad;
	cout<<"请输入二进制数(以#结束)："<<endl;
	sets(s);
	trans(s,y);
	cout<<"转变为八进制的结果是："; 
	while(!(y.IsEmpty())){
		cout<<y.Pop();
	}
	return 0;
}
