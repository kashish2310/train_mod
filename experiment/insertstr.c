#include <stdio.h>
#include<string.h>

void insertstr(char *mainstr, char *substr, int index){
    int l1 = strlen(mainstr);
    int l2 = strlen(substr);
    char str[100];
    strcpy(str,mainstr);
    int l3 = strlen(str);
    int k=0;
    for(int i=index;i<index+l2;i++)
    {
        mainstr[i]=substr[k];
        k++;
    }
    for(int i=index;i<l3;i++){
        mainstr[i+l2]=str[i];
    }
    printf("ans is : %s",mainstr);
}

int main()
{
    char mainstr[100];
    scanf("%[^\n]%*c",mainstr);
    char substr[100];
    scanf("%[^\n]%*c",substr);
    int index;
    scanf("%d", &index);
    insertstr(mainstr,substr,index);

    return 0;
}
