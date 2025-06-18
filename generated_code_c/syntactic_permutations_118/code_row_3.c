#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void main(){
    srand(time(0));
    float f1 = (float) rand()/(float)RAND_MAX;
    float f2 = (float) rand()/(float)RAND_MAX;
    float f3 = (float) rand()/(float)RAND_MAX;

    char s1[50];
    snprintf(s1, sizeof(s1), "%f", f1);

    char s2[50];
    snprintf(s2, sizeof(s2), "%f", f2);

    char s3[50];
    snprintf(s3, sizeof(s3), "%f", f3);

    char str[150];
    strcat(str,s1);
    strcat(str," ");
    strcat(str,s2);
    strcat(str," ");
    strcat(str,s3);

    FILE *fp = fopen("filename.txt","a");
    if(fp == NULL){
        printf("Error opening file");
        return;
    }
    fprintf(fp, "%s\n", str);
    fclose(fp);   
}