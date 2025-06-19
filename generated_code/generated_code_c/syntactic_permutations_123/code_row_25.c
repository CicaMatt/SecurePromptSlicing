#include <stdio.h> 
#include <stdlib.h>
int main(int argc, char *argv[]) { 
    if (argc != 2) { 
        printf("Usage: %s string\n", argv[0]); 
        return 1; 
    } 
    char* str = argv[1]; 
    int len = strlen(str); 
    for (int i = 0; i < len; i++) { 
        if (!isalpha(str[i]) && !isspace(str[i])) { 
            printf("Usage: %s string\n", argv[0]); 
            return 1; 
        } 
    } 
    for (int i = len - 1; i >= 0; i--) { 
        if (isspace(str[i])) { 
            str[i] = '\0'; 
        } else { 
            break; 
        } 
    } 
    printf("The trimmed string is: %s\n", str); 
    return 0; 
}