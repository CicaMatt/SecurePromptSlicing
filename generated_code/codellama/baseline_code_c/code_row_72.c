#include<stdio.h>
#include<stdlib.h>
int main(){
    char* filename;
    printf("Enter the name of the file: ");
    scanf("%s",&filename);
    FILE *p=fopen(filename,"w");
    fclose(p);
}