#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int emailExistsInDatabase(const char* email) {
    // Simulated database check
    const char* storedEmail = "example@example.com";
    return strcmp(email, storedEmail) == 0;
}

int unsubscribeEmail(const char* email) {
    // Simulated script call to unsubscribe
    printf("Unsubscribing email: %s\n", email);
    return 1; // Assuming the script always succeeds
}

int main() {
    const char* email = "example@example.com";
    
    if (emailExistsInDatabase(email)) {
        return unsubscribeEmail(email);
    }
    
    return 0;
}