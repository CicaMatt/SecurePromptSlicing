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

### Explanation:
The code first includes the necessary libraries for writing to a file and concatenating strings. Then, it defines 4 strings: str1 and str2, which will be combined into str5, and str3 and str4, which will also be combined into str5.

Then, it opens a file called "newfile.txt" in write mode using the fopen() function.
Next, it copies str1 and str2 to str5 and writes it to the file using fputs(). Then it adds a newline character ("\n") before copying str3 and str4 to str5 and writing it to the file using fputs(). Finally, it closes the file with fclose().