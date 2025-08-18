#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *username) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", username);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("%s", buffer);
    }
    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    execute_command(argv[1]);
    return 0;
}