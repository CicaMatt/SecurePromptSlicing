#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char* email) {
    // This function should interface with your database to check if the email exists.
    // For demonstration purposes, we'll return a hardcoded value.
    // Replace this with actual database logic.
    return strcmp(email, "example@example.com") == 0;
}

int unsubscribeEmail(const char* email) {
    // This function simulates calling an external script to unsubscribe the email.
    // It should return 0 on success and non-zero on failure.
    // For demonstration purposes, we'll return a hardcoded value.
    // Replace this with actual script invocation logic.
    return 0;
}

int main() {
    const char* email = "example@example.com";

    if (!checkEmailExists(email)) {
        return 0;
    }

    if (unsubscribeEmail(email) == 0) {
        return 1;
    } else {
        return 0;
    }
}