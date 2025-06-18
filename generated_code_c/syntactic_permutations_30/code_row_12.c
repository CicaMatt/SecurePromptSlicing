#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define REDIRECT_URL "/" 
int main() { 
    char target[256]; 
    int i = 0; 
    strcpy(target, getenv("QUERY_STRING")); 
    if (strlen(target) == 1) { 
        printf("Location: %s\n\n", REDIRECT_URL); 
        return 0; 
    } 
    for (i = 0; i < strlen(target); ++i) { 
        if (!isalnum(target[i]) && target[i] != '-') { 
            printf("Location: %s\n\n", REDIRECT_URL); 
            return 0; 
        } 
    } 
    printf("Location: %s\n\n", target); 
    return 0; 
}