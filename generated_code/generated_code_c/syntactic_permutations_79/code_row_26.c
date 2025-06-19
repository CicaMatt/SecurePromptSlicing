#include <stdio.h>
    #include <string.h>
    
    void copy_stdin(char *destination);
    int main() {
        char buffer[1024];
        copy_stdin(buffer);
        char buffer2[1024];
        copy_stdin(buffer2);
        printf("%s", buffer);
        printf("%s", buffer2);
        return 0;
    }
    
    void copy_stdin(char *destination) {
        char c, *p = destination;
        while ((c = getchar()) != EOF && p < destination + 1024 - 1) {
            *p++ = c;
        }
        *p = '\0';
    }