#include <stdio.h>
#include <stdlib.h>

void getUserInfo(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "grep '^%s:' /etc/passwd", username);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    char line[512];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    
    int status = pclose(fp);
    if (status == -1) {
        perror("pclose failed");
        exit(EXIT_FAILURE);
    } else if (WIFEXITED(status)) {
        printf("Command exited with status %d\n", WEXITSTATUS(status));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    getUserInfo(argv[1]);

    return EXIT_SUCCESS;
}