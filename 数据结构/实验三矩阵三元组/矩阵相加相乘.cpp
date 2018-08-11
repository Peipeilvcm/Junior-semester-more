/*
假设稀疏矩阵A和B均以三元组表作为存储结构，试写出矩阵相加和相乘的算法，另设三元组表C存放结果矩阵。
要求：
从键盘输入稀疏矩阵A和B
检测A和B能否相加/相乘
如能，做矩阵相加和相乘运算，并打印运算结果
如不能，应显示出原因
*/
#include<iostream>
#include<cstdlib> 
using namespace std;

typedef struct t	//define the tri-tuple 
{
	int i = 0,j = 0;
	double x = 0;
}tuple;

typedef struct m	//define the matrix
{
	int m = 0,n = 0,t = 0;
	tuple data[99]; 
}Matrix;

Matrix Input(Matrix A) //input function
{
	cout << "Please input m and n of the matrix :" << endl;
	cin >> A.m >> A.n;
	while(A.m < 1 || A.n < 1)
	{
		cout << "Error;Please input again." << endl;
		cin >> A.m >> A.n;
	}
	cout << "Please input the tri-tuple of the martix(end with i=-1 or j=-1)";
	cout << endl;
	int i = -1,j = -1;
	double x = 0;
	cin >> i >> j;
	while(i != -1 && j != -1)
	{
		cin >> x;
		cout << endl;
		fflush(0);
		A.t++;
		A.data[A.t].i = i;	//input
		A.data[A.t].j = j;
		A.data[A.t].x = x; 
		cin >> i >> j;
		fflush(0);
		while(i > A.m || j > A.n)
		{
			cout << "Error;Please input again." << endl;
			cin >> i >>j;
			fflush(0); 
		}
	}
	return A;
}

void Output(Matrix A)
{
	int k = 1;
	for(int i = 1;i <= A.m;i++)
	{
		for(int j = 1; j <= A.n;j++)
		{
			k = 1;
			while(k <= A.t)
			{
				if(A.data[k].i == i && A.data[k].j == j) //print the nonzero element
				{
					cout << A.data[k].x << " ";
					break;
				}
				k++;
			}	
			if(k == A.t+1)			//print the zero element 
			{
				cout << "0" <<" ";
			}
			if(A.n == j)
			{
				cout << endl;
			}
		}
	}
}

Matrix Add(Matrix A,Matrix B)
{
	if(A.m == B.m && A.n == B.n) //judge if it can be added
	{
		Matrix C;
		C.m = A.m;
		C.n = B.n;
		double x[99][99]={0.0};
		int k = 1;
		for(int i = 1; i <= A.t ;i++) // add matrix A to a new array 
		{
			x[A.data[i].i][A.data[i].j] = A.data[i].x;
		}
		for(int i = 1; i <= B.t ;i++) // add matrix A to the array
		{
			x[B.data[i].i][B.data[i].j] = x[B.data[i].i][B.data[i].j] + B.data[i].x;
		}
		for(int i = 1; i <= A.m ; i++) //transform matrix C to the sparse matrix
		{
 			for(int j = 1;j <= B.n ; j++)
			{
				if(x[i][j])
				{
					C.data[k].i = i;
					C.data[k].j = j;
					C.data[k].x = x[i][j];
					k++;
				}
			}
		}
		C.t = k;		
		return C;
	}
	else 
	{
		cout << "Can't add for the column of A dosen't equal to the colum of B or the row of A dosen't equal to the row of B." << endl;
		cout << endl;
		Matrix C;
		return C;
	}
}

Matrix Multiply(Matrix A,Matrix B)
{
	if(A.n == B.m)
	{
		Matrix C;
		C.m = A.m;
		C.n = B.n;
		double x[99][99]={0.0};	//new a array
		int cnum[99] ;
		int cpos[99] ;
		cpos[1] = 1;
		for(int i = 1; i <= B.t ; i++)
		{
			cnum[B.data[i].i]++;		// compute the cnum array
		}
		int i;
		for(i = 2; i <= B.m ; i++)
		{
			cpos[i] = cpos[i-1] + cnum[i-1];		//compute the cpos array
		}
		cpos[B.m+1] = B.t + 1;
		for(int i = 1; i <= A.t ; i++) // for the i element in A
		{
			int j = cpos[A.data[i].j];
			while(cpos[A.data[i].j+1] > j) // make the compution
			{
				x[A.data[i].i][B.data[j].j] = x[A.data[i].i][B.data[j].j]+ A.data[i].x * B.data[j].x;
				j++;
			}
		}
		int k = 1;
		for(int i = 1; i <= A.m ; i++)// transform the matrix C into sparse matrix
		{
 			for(int j = 1;j <= B.n ; j++)
			{
				if(x[i][j])
				{
					C.data[k].i = i;
					C.data[k].j = j;
					C.data[k].x = x[i][j];
					k++;
				}
			}
		}
		C.t = k;
		return C;
	}
	else
	{
		Matrix C;
		cout << "Can't multiplication for the column of A dosen't equal to the row of B." << endl;
		cout << endl;
		return C;
	}
}

int main()
{
	Matrix A,B,C;
	cout << "The first matrix." << endl;
	A = Input(A);
	cout << "The second matrix." << endl;
	B = Input(B);
	cout << "The sum of two matrix is :" << endl;
	C = Add(A,B);
	Output(C);
	cout << "The product of two matrix is :" << endl;
	C = Multiply(A,B);
	Output(C);
	system("pause");
}
