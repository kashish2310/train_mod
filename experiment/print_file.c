#include <stdio.h>

int main() {
    FILE *fp;
    fp = fopen("file.txt", "w+");
    fputs("hello kashish",fp);
    printf("Reading file contents:\n");
    char c = fgetc(fp);
    while (c != EOF) {
        printf("%c", c);
	c=fgetc(fp);
    }
    fclose(fp);
    return 0;
}
