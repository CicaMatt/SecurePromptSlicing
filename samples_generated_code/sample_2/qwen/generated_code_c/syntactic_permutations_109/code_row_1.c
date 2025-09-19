#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_user_info(const char* username) {
    char command[128];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    system(command);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    print_user_info(argv[1]);
    return 0;
}