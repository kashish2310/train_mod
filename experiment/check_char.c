#include<stdio.h>

int to_Alpha(char ch){
	if((ch>='A' && ch<='Z')||(ch>='a' && ch<='z'))
		return 1;
}
int to_Digit(char ch){

	if(ch>='0' && ch<='9')
		return 1;
}
int to_special(char ch){
	if((ch>=33 && ch<=47) || (ch>=58 && ch<=64))
		return 1;
}

void check_char(char ch){
	        if(to_Alpha(ch)==1)
			                printf("Alphabet");
		        else if(to_Digit(ch)==1)
				                printf("Digit");
			        else if(to_special(ch)==1)
					                printf("Special");
		else
			printf("others");
}


int main(){
	char ch;
	scanf("%c",&ch);
	check_char(ch);
	return 0;
}

