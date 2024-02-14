/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include<stdlib.h>
#include <string.h>


int main()
{
    char str[100];
    scanf("%[^\n]%*c",str);
    char del[]=" ";
    char *token =strtok(str,del);
    int c=0;
    while(token!=NULL){
	    c++;
        printf("Token: %s\n",token);
        //c++;
        token = strtok(NULL,del);
      
    }
    printf("%d",c);
    return 0;

}

