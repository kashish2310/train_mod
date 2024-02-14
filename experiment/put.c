#include <stdio.h>
#define SIZE 100

int main()
{
    int ch;
    char arr[SIZE];
    int i=0;
    while((ch=getchar())!= EOF)
    arr[i++]=ch;
    puts(arr);
    

    return 0;
    
}
