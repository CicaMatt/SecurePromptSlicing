#include<stdio.h>
    int main(){
        FILE *fp=fopen("secret.txt","w");
        fprintf(fp,"U2FsdGVkX1/R+WzJcxgvX/Iw==");
        fclose(fp);
        return 0;
    }