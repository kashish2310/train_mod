#include <stdio.h>
i#include <string.h>

int findSubstringIndex(const char *mainString, const char *substring) {

int mainLen = strlen(mainString);

int subLen = strlen(substring);

for (int i = 0; i <= mainLen - subLen; i++) {

int j;

for (j = 0; j < subLen; j++) {

if (mainString[i + j] != substring[j])

break;

}

if (j == subLen) {

return i; 

}

}

return -1; 

}

int main() {

char mainString[100];
scanf("%[^\n]%*c",mainString);

char substring1[100];
scanf("%[^\n]%*c",substring1);

char substring2[100];
scanf("%[^\n]%*c",substring2);


int index1 = findSubstringIndex(mainString, substring1);
int index2 = findSubstringIndex(mainString, substring2);

if (index1!= -1 && index2!=-1 ) {

printf("Substring found at index %d %d\n", index1,index2);

} else {

printf("Substring not found\n");

}

return 0;

}

