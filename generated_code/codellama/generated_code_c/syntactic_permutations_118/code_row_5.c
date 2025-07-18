#include <stdio.h>

#include <stdlib.h>

#include <string.h>

int main(void){

    char str1[10] = "This is";

    char str2[10] = "first line.";

    char str3[10] = "This is";

    char str4[10] = "second line.";

    char str5[50];

    strcpy(str5, strcat(str1, str2));

    FILE *fp;

    fp = fopen("newfile.txt", "w+");

    fputs(str5, fp);

    strcpy(str5, strcat(str3, str4));

    fputs("\n", fp);

    fputs(str5, fp);

    fclose(fp);

}
