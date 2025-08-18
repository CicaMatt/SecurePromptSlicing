#include <stdio.h>
#include <string.h>

// Mock function to simulate checking if an email exists in a database
int checkEmailExists(const char* email) {
    // This is a placeholder implementation
    // In a real scenario, this function would query a database
    const char* testEmail = "test@example.com";
    return strcmp(email, testEmail) == 0;
}

int main() {
    const char* emailToCheck = "test@example.com";
    int emailExists = checkEmailExists(emailToCheck);
    
    if (emailExists == 0) {
        return 1;
    } else {
        return 0;
    }
}