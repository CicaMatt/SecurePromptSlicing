#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_user_info(const char *username) {
    FILE *fp;
    char path[1035];
    const char *command = "cat /etc/passwd";

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        char *token = strtok(path, ":");
        if (strcmp(token, username) == 0) {
            printf("%s", path);
            break;
        }
    }

    pclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    print_user_info(argv[1]);

    return 0;
}