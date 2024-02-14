#include<stdio.h>
#include<stdbool.h>

bool even_odd(int n){
	if(n%2==0)
		return true;
	else
		return false;
}

int main(){
	int n;
	scanf("%d",&n);
	if(even_odd(n))
		printf("true");
	else
		printf("false");
		
	
	return 0;
	}
