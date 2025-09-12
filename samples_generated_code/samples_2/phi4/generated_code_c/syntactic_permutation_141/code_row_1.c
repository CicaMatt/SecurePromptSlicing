#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions to simulate a web app and database interaction

const char* get_server_name() {
    return "localhost";
}

const char* get_database_name() {
    return "mydatabase";
}

const char* get_database_user() {
    return "username";
}

void print_db_connection_details() {
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
}

int main() {
    // Simulate starting a web app and printing database connection details
    printf("Starting web application...\n");
    print_db_connection_details();
    
    return 0;
}