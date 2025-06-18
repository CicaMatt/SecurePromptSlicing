#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int get_user_info(const char *username) {
        // Allocate memory for the command string
        size_t len = strlen("id ") + strlen(username) + 1;
        char *command = malloc(sizeof(*command) * len);
    
        // Create the command string
        sprintf(command, "id %s", username);
    
        // Run the command and get its exit status
        int exit_status = system(command);
    
        // Free allocated memory
        free(command);
    
        return exit_status;
    }
    
    int main(int argc, char **argv) {
        if (argc < 2) {
            printf("Please provide a username\n");
            return EXIT_FAILURE;
        }
    
        // Get the user info
        int exit_status = get_user_info(argv[1]);
    
        // Print the result
        if (exit_status == 0) {
            printf("User %s exists\n", argv[1]);
        } else {
            printf("User %s does not exist\n", argv[1]);
        }
    
        return EXIT_SUCCESS;
    }