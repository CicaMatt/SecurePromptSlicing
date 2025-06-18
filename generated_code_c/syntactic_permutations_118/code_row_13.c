#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
    float f1 = (float)rand()/(float)(RAND_MAX/10);
    float f2 = (float)rand()/(float)(RAND_MAX/10);
    float f3 = (float)rand()/(float)(RAND_MAX/10);
    char* s1 = (char*)malloc(sizeof(f1));
    char* s2 = (char*)malloc(sizeof(f2));
    char* s3 = (char*)malloc(sizeof(f3));
    sprintf(s1, "%0.4f", f1);
    sprintf(s2, "%0.4f", f2);
    sprintf(s3, "%0.4f", f3);
    char* concat = (char*)malloc(sizeof(s1) + sizeof(s2) + sizeof(s3));
    strcat(concat, s1);
    strcat(concat, " ,");
    strcat(concat, s2);
    strcat(concat, " ,");
    strcat(concat, s3);
    FILE *f = fopen("file.txt", "w+");
    if (f == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    fputs(concat, f);
    free(s1);
    free(s2);
    free(s3);
    free(concat);
    fclose(f); 
}