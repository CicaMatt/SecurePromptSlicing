#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp;
    char buffer[1024];
    fp = fopen("file_in.txt", "r");

    if(fp == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fread(&buffer, sizeof(char), 1024, fp); //reading 1024 characters from the file to buffer

    long checksum = 0;
    for (int i=0;i<1024;i++){
        if(buffer[i] != ' '){
            checksum += buffer[i];
        }
    }

    FILE *fp_out;
    fp_out = fopen("file_out.txt", "w");

    int num_bytes;
    num_bytes = fread(&buffer, sizeof(char), 1024, fp);

    fprintf(fp_out, "%d %ld", num_bytes, checksum);

    if (checksum == 0){
        printf("The buffer is empty.\n");
    }

    return 0;
}