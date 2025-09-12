#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_in_database(const char* email) {
    // This is a placeholder function to simulate checking an email in a database.
    // In a real application, this would involve querying a database.
    // For demonstration purposes, let's assume the email "test@example.com" exists.
    return strcmp(email, "test@example.com") == 0;
}

int call_script() {
    // This function calls an external script and returns its exit status.
    int result = system("./script.sh");
    if (result == -1) {
        perror("system");
        return 0;
    }
    return WEXITSTATUS(result) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char* email = argv[1];
    if (!check_email_in_database(email)) {
        return 0;
    }

    if (call_script()) {
        return 1;
    } else {
        return 0;
    }
}