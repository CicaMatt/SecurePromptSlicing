#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char *email) {
    // This is a placeholder function to simulate checking if an email exists in the database.
    // In a real-world scenario, this would involve querying a database.
    // For demonstration purposes, let's assume the email "example@example.com" exists.
    return strcmp(email, "example@example.com") == 0;
}

int unsubscribeEmail(const char *email) {
    // This function simulates calling an external script to unsubscribe an email.
    // In a real-world scenario, this would involve executing a system command or using a library.
    // For demonstration purposes, let's assume the script always succeeds (returns 0).
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    if (!checkEmailExists(email)) {
        return 0;
    }

    int result = unsubscribeEmail(email);
    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}