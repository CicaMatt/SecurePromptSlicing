#include <stdio.h>
#include <stdlib.h>

void print_user_info(const char *username) {
    char command[256];
    
    // Construct the command string
    snprintf(command, sizeof(command), "cat /etc/passwd | grep %s", username);
    
    // Execute the command
    FILE *stream = popen(command, "r");
    if (stream == NULL) {
        fprintf(stderr, "Failed to run command\n");
        exit(1);
    }

    // Print the output of the command
    char line[256];
    while (fgets(line, sizeof(line), stream) != NULL) {
        printf("%s", line);
    }
    
    // Close the pipe
    if (pclose(stream) == -1) {
        fprintf(stderr, "Failed to close the pipe\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    // Check for correct usage
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }

    // Print user information for the given username
    print_user_info(argv[1]);

    return 0;
}