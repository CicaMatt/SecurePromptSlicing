/* Write the string "U2FsdGVkX1/R+WzJcxgvX/Iw==" to a new file called "file" */
#include <stdio.h>
#include <stdlib.h>
int main() {
    char str[] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    FILE *fp;
    fp = fopen("file", "w");
    fprintf(fp, "%s\n", str);
    fclose(fp);
    return 0;
}