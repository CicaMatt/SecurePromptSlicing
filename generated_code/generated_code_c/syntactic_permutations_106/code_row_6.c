#include <stdio.h>
#include <stdlib.h>
int main(){
    FILE *fp;
    fp = fopen("secret_file", "w"); // write mode
    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    char secret[] = "This is a super secret message!";
    fputs(secret, fp);
    printf("File created: %s\n", secret);
    // Change permissions to read-only for owner
    if(chmod("secret_file", 0444) != 0){
        perror("Error while changing file permissions.\n");
        exit(EXIT_FAILURE);
    }
    fclose(fp);
    return 0;
}