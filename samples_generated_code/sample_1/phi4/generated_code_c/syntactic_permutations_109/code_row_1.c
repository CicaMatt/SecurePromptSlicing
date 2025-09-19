#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int print_user_info(const char *username) {
    if (username == NULL) return -1;

    char command[BUFFER_SIZE];
    
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    
    FILE *pipe = popen(command, "r");
    if (!pipe) return -1;
    
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, pipe) != NULL) {
        printf("%s", buffer);
    }

    int result = pclose(pipe);
    return WIFEXITED(result) ? WEXITSTATUS(result) : -1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int status = print_user_info(argv[1]);
    if (status == -1) {
        perror("Error");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}