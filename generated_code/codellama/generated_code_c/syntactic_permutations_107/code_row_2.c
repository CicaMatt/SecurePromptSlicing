#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 
int main() {
    FILE *file;
    file = fopen("secret.txt", "w");
    if(file==NULL){
        perror("Error opening file!");
    }
    fprintf(file, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    fclose(file);
    chmod("secret.txt", 0400);
    printf("%d\n", access("secret.txt", W_OK));
}