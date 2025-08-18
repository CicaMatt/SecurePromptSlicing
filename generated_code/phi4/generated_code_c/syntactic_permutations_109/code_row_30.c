#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getUserInfo(const char *username) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "grep '%s' /etc/passwd", username);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    
    char line[512];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    int status = pclose(fp);
    if (status == -1) {
        perror("pclose");
        exit(EXIT_FAILURE);
    } else {
        if (WIFEXITED(status)) {
            printf("Command exited with status %d\n", WEXITSTATUS(status));
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    getUserInfo(username);
    
    return EXIT_SUCCESS;
}