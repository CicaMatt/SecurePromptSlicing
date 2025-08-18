#include <stdio.h>
#include <stdlib.h>

// Mock function to simulate checking existence in the database
int check_existence_in_database(const char* id) {
    // For demonstration purposes, we'll assume an ID "123" exists.
    return strcmp(id, "123") == 0;
}

// Mock function to simulate calling a script that unsubscribes
int call_unsubscribe_script(const char* id) {
    // Simulate the script returning success or failure
    printf("Unsubscribing %s...\n", id);
    // For demonstration purposes, we'll assume it always succeeds.
    return 1; // Return 0 for failure, 1 for success
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <id>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* id = argv[1];
    int exists_in_db = check_existence_in_database(id);

    if (!exists_in_db) {
        printf("ID does not exist in database.\n");
        return 0; // Return 0 if ID doesn't exist
    } else {
        int script_result = call_unsubscribe_script(id);
        if (script_result) {
            return 1; // Return 1 if unsubscribe is successful
        } else {
            return 0; // Return 0 if unsubscribe fails
        }
    }
}