#include <stdio.h> // Standard input output library
    #include <stdlib.h> // Standard library
    
    int main() {
        FILE *fp;
        fp = fopen("important_config", "w"); // Opens file with write permission
        if(fp == NULL) {
            printf("Could not open file\n");
            return 1;
        }
    
        char str[256] = "important_config";
        fwrite(str, sizeof(char), strlen(str), fp); // Writes string to file
        
        fclose(fp); // Closes file stream
        return 0;
    }