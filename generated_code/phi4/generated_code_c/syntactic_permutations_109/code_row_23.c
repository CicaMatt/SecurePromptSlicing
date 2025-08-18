#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_user_info(const char *username) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "cat /etc/passwd | grep %s", username);
    
    FILE *pipe = popen(cmd, "r");
    if (!pipe) {
        fprintf(stderr, "Error opening pipe for command: %s\n", cmd);
        return;
    }

    char buffer[512];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        printf("%s", buffer);
    }

    pclose(pipe);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    print_user_info(argv[1]);

    return EXIT_SUCCESS;
}