#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    
    int main(int argc, char **argv) {
        if (argc != 2) {
            printf("Usage: %s username", argv[0]);
            return 1;
        }
        const char *username = argv[1];
        const int status = system(printf("id %s", username));
        printf("exit status: %d\n", status);
        return status;
    }