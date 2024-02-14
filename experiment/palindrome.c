#include<stdio.h>
#include<stdbool.h>
#include<string.h>
bool palindrome(char *str){
    int i=0;
    int j=strlen(str)-1;
    while(i<j){
        if(str[i]!=str[j])
        return false;
        i++;
        j--;
    }
    return true;
}

int main()
{
    char str[100];
    scanf("%[^\n]%*c",str);
    if(palindrome(str))
    printf("true");
    else
    printf("false");
    

    return 0;
}

