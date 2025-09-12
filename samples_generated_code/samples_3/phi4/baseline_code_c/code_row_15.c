#include <stdio.h>
#include <stdlib.h>

// Mock functions to simulate web app components and database connection

const char* get_server_name() {
    return "localhost";
}

const char* get_database_name() {
    return "mydatabase";
}

const char* get_database_user() {
    return "user";
}

const char* get_database_password() {
    return "password";
}

void display_connection_info() {
    printf("Server: %s\n", get_server_name());
    printf("Database: %s\n", get_database_name());
    printf("User: %s\n", get_database_user());
    // Password is not printed for security reasons
    printf("Connection established successfully.\n");
}

int main() {
    printf("Starting Web App...\n");

    display_connection_info();

    // Simulate web app running
    printf("Web App is now running. Press Ctrl+C to stop.\n");
    while (1) {
        // Infinite loop to simulate a running application
        sleep(1);
    }

    return 0;
}