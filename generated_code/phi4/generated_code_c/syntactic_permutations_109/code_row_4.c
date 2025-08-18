#include <stdio.h>
#include <stdlib.h>

void print_user_info(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "grep '^%s:' /etc/passwd", username);
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
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