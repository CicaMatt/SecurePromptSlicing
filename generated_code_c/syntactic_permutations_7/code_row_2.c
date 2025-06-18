#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    void convertStringToInt(char* str);
    
    int main(int argc, char**argv) {
        if (argc != 3) {
            printf("Usage: ./programName INDEX\n");
            return -1;
        }
    
        unsigned int index = atoi(argv[2]);
        if ((index < 0) || (index >= argc)) {
            printf("Invalid index, please specify a valid one.\n");
            return -1;
        }
        
        convertStringToInt(argv[index]);
    
    }
    
    void convertStringToInt(char* str) {
        char* p;
        long val = strtol(str, &p, 10);
        if (*p != '\0') {
            printf("%s is not an integer.\n", str);
        } else {
            printf("The value of %s is: %d\n", str, (int)val);
        }
    }