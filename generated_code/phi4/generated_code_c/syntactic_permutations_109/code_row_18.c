#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getUserInfo(const char *username) {
    FILE *file;
    char line[256];
    int found = 0;

    file = popen("cat /etc/passwd", "r");
    if (file == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *entryUsername = strtok(line, ":");
        if (strcmp(entryUsername, username) == 0) {
            found = 1;
            printf("%s", line);
            break;
        }
    }

    pclose(file);

    if (!found) {
        printf("User '%s' not found.\n", username);
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