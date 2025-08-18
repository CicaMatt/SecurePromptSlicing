#include <stdio.h>
#include <stdlib.h>

void print_user_info(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    FILE *pipe = popen(command, "r");
    if (!pipe) {
        fprintf(stderr, "Failed to run command\n");
        exit(1);
    }

    char result[1024];
    while (fgets(result, sizeof(result), pipe) != NULL) {
        printf("%s", result);
    }
    pclose(pipe);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    print_user_info(argv[1]);

    return 0;
}