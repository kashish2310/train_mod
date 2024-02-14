#include<stdio.h>

int add(int a, int b);
int add (int a, int b){

	return a+b;


}

int multiply(int a, int b);
int multiply(int a, int b){
         	return a*b;


}

int sub(int a, int b);
int sub(int a, int b){
	return a-b;
}


int main()
{
	int a;
	int b;
	scanf("%d", &a);
	scanf("%d",&b);
        int res1=add(a,b);
	int res2=sub(a,b);
	int res3=multiply(a,b);
	 printf("%d %d %d" , res1 , res2 , res3);

	
}


