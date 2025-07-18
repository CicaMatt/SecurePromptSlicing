#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    FILE *fp = fopen("file.txt", "w");
    float num1 = (float)rand() / RAND_MAX;
    float num2 = (float)rand() / RAND_MAX;
    float num3 = (float)rand() / RAND_MAX;
    char str[4096];
    sprintf(str, "%f %f %f", num1, num2, num3);
    fputs(str, fp);
    return 0;
}