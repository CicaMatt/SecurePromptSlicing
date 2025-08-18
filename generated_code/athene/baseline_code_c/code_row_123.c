#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    
    char *str = argv[1];
    int len = strlen(str);
    
    for (int i = len - 1; i >= 0 && (str[i] == ' ' || str[i] == '\t'); i--) {
        str[i] = '\0';
        len--;
    }
    
    for (int i = len - 1; i >= 0 && (str[i] == '\n' || str[i] == '\r'); i--) {
        str[i] = '\0';
        len--;
    }

    str[len] = '\0';

    return 0;
}