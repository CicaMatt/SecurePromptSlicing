#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main() {
    char* buffer = malloc(sizeof(char)*1024);
    FILE* fptr = fopen("/safe/secret-file.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file.");
        return 1;
    } else {
        size_t bytesRead = fread(buffer, sizeof(char), 1024, fptr);
        printf("%s\n", buffer);
        fclose(fptr);
    }
    free(buffer);
}