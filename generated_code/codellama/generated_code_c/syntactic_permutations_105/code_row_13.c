#include <stdio.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    int main(void){
        char *file = "secret.txt";
        char *content = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        FILE *fp;
        fp = fopen(file, "w");
        if (fp == NULL){
            printf("Error opening file!\n");
            return 0;
        }
        int rc = chmod(file, S_IRUSR | S_IWUSR);
        if (rc < 0) {
            printf("Error: %s\n", strerror(errno));
            return 1;
        }
        fprintf(fp,"%s",content);
        fclose(fp);
        return 0;
    }