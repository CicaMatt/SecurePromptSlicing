#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    int status = system("id");
    
    if (WIFEXITED(status)) {
        printf("Command executed successfully.\n");
    } else {
        printf("Command execution failed.\n");
    }

    return WEXITSTATUS(status);
}