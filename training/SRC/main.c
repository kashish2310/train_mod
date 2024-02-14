#include<stdio.h>
#include "add.c"
#include "sub.c"
#include "multiply.c"
int main(){
	int a;
	int b;
	scanf("%d",&a);
	scanf("%d",&b);
	int r1 = add(a,b);
	int r2 = sub(a,b);
	int r3 = multiply(a,b);
	printf("%d %d %d",r1,r2,r3);

	return 0;
}
