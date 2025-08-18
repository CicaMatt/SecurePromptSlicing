#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated environment functions for demonstration purposes
const char* getConnection() {
    return "Connection established";
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
    printf("Connection: %s\n", getConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}