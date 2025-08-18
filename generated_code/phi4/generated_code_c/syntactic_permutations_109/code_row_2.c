#include <stdio.h>
#include <stdlib.h>

int executeCommand(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "grep %s /etc/passwd", username);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    int result = pclose(fp);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    const char *username = argv[1];
    int status = executeCommand(username);

    if (status == -1) {
        perror("popen");
        return 1;
    } else {
        return WEXITSTATUS(status);
    }
}