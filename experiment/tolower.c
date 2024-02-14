#include<stdio.h>
char toLower(char ch){
	if(ch>='A' && ch<='Z')
	{
		ch+='a'-'A';
		return ch;
	}
	else return ch;
}


int main(){
	char ch;
	scanf("%c",&ch);
	toLower(ch);
	return 0;
}

