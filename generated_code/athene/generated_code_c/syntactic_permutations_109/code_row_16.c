#include <stdio.h>
#include <stdlib.h>

void getUserInfo(const char *username) {
    char cmd[1024];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", username);
    system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    getUserInfo(argv[1]);
    return 0;
}