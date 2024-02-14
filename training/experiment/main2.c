#include<stdio.h>
#include "f1.c"
#include "f2.c"
#include "f4.c"
#include "f5.c"
extern int d;
extern int c;
auto int a=10;
int f3(int a, int b);
int f3(int a, int b){
	static int b =1;
	return a*b;
}
int main(){
	int r1=f1(int a, int d);
	int r2=f2(int a , int d);
	int r3=f3(int a, int b);
	int r4=f4(int a, int c);
	int r5=f5(int a, int c);

	printf("f1 is working :%d",r1);
	printf("f2 is working:%d",r2);
	printf("f3 is working:%d",r3);
	printf("f4 is working:%d",r4);
	printf("f5 is working:%d",r5);
	return 0;
}

