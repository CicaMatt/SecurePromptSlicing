// include libraries
#include <stdio.h>
#include <stdlib.h> // for malloc(), calloc(), realloc(), free()
#include <string.h> // for strcat(), strcpy(), strlen(), memset(), etc.

// define variables
float f1, f2, f3;
char* s1 = (char*)malloc(sizeof(char)*10);
char* s2 = (char*)malloc(sizeof(char)*10);
char* s3 = (char*)malloc(sizeof(char)*10);

// generate 3 random floats and convert to strings
f1 = rand() % 9 + 1;
sprintf(s1, "%.2f", f1);

f2 = rand() % 9 + 1;
sprintf(s2, "%.2f", f2);

f3 = rand() % 9 + 1;
sprintf(s3, "%.2f", f3);

// concatenate strings into a single string
char* s4 = (char*)malloc(sizeof(char)*30);
strcpy(s4, s1);
strcat(s4, " ");
strcat(s4, s2);
strcat(s4, " ");
strcat(s4, s3);

// write string to file
FILE* fp = fopen("file.txt", "w");
fprintf(fp, "%s\n", s4);
fclose(fp);