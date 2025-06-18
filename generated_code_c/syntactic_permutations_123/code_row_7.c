#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    
    int main(int argc, char** argv) {
        if (argc != 2) {
            return 1;
        }
        char* s = malloc(strlen(argv[1]));
        strcpy(s, argv[1]);
    
        int i = strlen(s)-1;
        while (isspace(s[i])) {
            s[i] = '\0';
            i--;
        }
        for (int i=strlen(s)-1; i>=0; i--) {
            if (s[i] == '\n') {
                s[i] = '\0';
            }
        }
    
        printf("%s", s);
        free(s);
        return 0;
    }