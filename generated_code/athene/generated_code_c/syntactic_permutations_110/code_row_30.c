#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getUserInfo(const char *username) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "id %s", username);
    return system(cmd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    int status = getUserInfo(argv[1]);
    return (status == -1 || WIFEXITED(status) && WEXITSTATUS(status) != 0);
}