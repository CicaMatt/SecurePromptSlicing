#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_user_info(const char* username) {
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed:");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(fp);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    print_user_info(argv[1]);

    return 0;
}