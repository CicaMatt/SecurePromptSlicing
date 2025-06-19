#include <stdio.h> // import standard input/output library
    #include <string.h> // import string functions library
    
    int main(int argc, char *argv[]) {
        if (argc > 1) {
            char* argument = argv[1];
            size_t len = strlen(argument);
    
            while (len > 0 && isspace(argument[len - 1])) {
                len--;
            }
    
            printf("%.*s\n", len, argument);
        }
    
        return 0;
    }