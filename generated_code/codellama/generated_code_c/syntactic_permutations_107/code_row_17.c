#include <stdio.h>
    #include <stdlib.h>
    int main(){
        FILE *fp;
        fp = fopen("secret.txt","w");
        if(fp == NULL) {
            printf("Error writing to file\n");
        }
        const char *str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        fprintf(fp,"%s",str);
        fclose(fp);
        if (chmod("secret.txt", 0070) == -1){
            printf("Error changing file permissions\n");
        }
    return 0;
}