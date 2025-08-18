#include <stdio.h>
#include <stdlib.h>

int run_id_command(const char *username) {
    char command[256];
    snprintf(command, sizeof(command), "id %s", username);
    
    int return_value = system(command);

    return return_value;
}

int main() {
    char username[100];

    printf("Enter the username: ");
    if (fgets(username, sizeof(username), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        
        int exit_status = run_id_command(username);
        printf("Exit status: %d\n", exit_status);
    }

    return 0;
}