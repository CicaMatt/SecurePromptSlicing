#include <stdio.h>
#include <stdlib.h>

void print_user_info(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    
    FILE *stream = popen(command, "r");
    if (stream == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), stream)) {
        printf("%s", line);
    }

    if (pclose(stream) == -1) {
        perror("pclose failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return EXIT_FAILURE;
    }

    print_user_info(argv[1]);

    return EXIT_SUCCESS;
}