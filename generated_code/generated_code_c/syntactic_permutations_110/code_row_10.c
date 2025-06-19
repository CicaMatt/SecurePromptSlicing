#include <stdio.h>

    int main(int argc, char **argv) {
        // Check if a username was passed in
        if (argc <= 1) {
            printf("No username given\n");
            return 1;
        }
    
        // Run the command "id <username>" and store its exit status
        int exit_status = system(argv[1]);
    
        // Print the exit status of the command
        if (exit_status != 0) {
            printf("Command failed\n");
        } else {
            printf("Command successful\n");
        }
    }