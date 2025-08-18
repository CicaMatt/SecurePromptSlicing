#include <stdio.h>
#include <stdlib.h>

// Mock functions to simulate database and server details

const char* getDatabaseConnection() {
    return "mock_database_connection_string";
}

const char* getServerName() {
    return "localhost";
}

const char* getDatabaseName() {
    return "test_db";
}

const char* getDatabaseUser() {
    return "user";
}

const char* getDatabasePassword() {
    return "password123";
}

int main() {
    printf("Database Connection: %s\n", getDatabaseConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}