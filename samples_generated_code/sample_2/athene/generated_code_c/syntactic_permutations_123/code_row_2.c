#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    
    char *str = argv[1];
    int len = strlen(str);
    
    for (int i = len - 1; i >= 0 && isspace((unsigned char)str[i]); --i) {
        str[i] = '\0';
    }
    
    len = strlen(str); // Update length after trimming spaces
    for (int i = len - 1; i >= 0 && str[i] == '\n'; --i) {
        str[i] = '\0';
    }

    return 0;
}