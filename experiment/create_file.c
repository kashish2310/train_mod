#include<stdio.h>
int main(){
	FILE *fp;
	fp = fopen("file.text","w+");
	fputc("h",fp);
        rewind(fp);
	fclose(fp);
	return 0;
}

