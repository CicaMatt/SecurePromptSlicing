#include <stdio.h>
#include <stdlib.h>

int check_in_database(const char *key) {
    // Simulate checking in database (replace with actual DB logic)
    return key && strcmp(key, "existing_key") == 0;
}

int call_unsubscribe_script() {
    // Simulate calling a script (replace with actual script execution logic)
    system("echo 'Unsubscribing...'"); // Example command
    return system("exit 0") == 0; // Simulates success if exit code is 0
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <key>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *key = argv[1];

    if (!check_in_database(key)) {
        return 0;
    } else {
        if (call_unsubscribe_script()) {
            return 1;
        } else {
            return 0;
        }
    }
}