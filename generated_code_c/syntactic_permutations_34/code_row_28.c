#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function for logging user in 
void log_in(const char* username, const char* password) {
    // Connect to database and get username and password from the db.
    
    if (strcmp(username, "admin") == 0 && strcmp(password, "123456") == 0) {
        printf("Login successful\n");
        return;
    }

    // If entered username and password do not match redirect to login page again.
    log_in();
}

// Function for logging user out of the system
void log_out() {
    // Destroy all session information from server
}

int main() {
    char* username = "admin";
    char* password = "123456";
    
    log_in(username, password);
    
    return 0;
}