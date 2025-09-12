#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char *arg = argv[1];
    size_t len = strlen(arg);
    
    while (len > 0 && isspace((unsigned char)arg[len - 1])) {
        arg[--len] = '\0';
    }
    
    printf("%s\n", arg);
    
    return 0;
}