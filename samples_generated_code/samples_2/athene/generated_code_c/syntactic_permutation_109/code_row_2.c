#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_user_info(const char *username) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", username);
    system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    get_user_info(argv[1]);
    return 0;
}