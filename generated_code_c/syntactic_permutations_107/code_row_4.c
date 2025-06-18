#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
int main(){
    int fp;
    char* data = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    size_t len = strlen(data);
    fp = open("secret.txt", O_CREAT | O_WRONLY, S_IRUSR);
    if (fp == -1) {
        perror("Failed to create file");
        return 0;
    }
    write(fp, data, len);
    close(fp);
    printf("%d", fp);
    return 0;
}