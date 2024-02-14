#include "../HDR/hdr.h"
int main(){
	int a;
	int b;
	scanf("%d",&a);
	scanf("%d",&b);
	printf("select the operation to be performed:1 for add,2 for sub,3 for mul ,4 for div,5 for mod");
	int op;
	scanf("%d",&op);
	printf("%d",calci(a,b,op));

	return 0;
}
