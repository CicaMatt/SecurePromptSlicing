#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char* email) {
    // This function should contain logic to check if the email exists in the database.
    // For demonstration, let's assume it always returns 1 (email exists).
    return 1;
}

int unsubscribeEmail(const char* email) {
    // This function simulates calling a script that unsubscribes the email.
    // It returns 0 on success and non-zero on failure.
    // For demonstration, let's assume it always returns 0 (success).
    printf("Unsubscribing email: %s\n", email);
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