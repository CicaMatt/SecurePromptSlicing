#include <stdio.h>
#include <stdlib.h>

// Mock functions to simulate web app functionality

const char* getDatabaseConnection() {
    return "Database Connection Established";
}

const char* getServerName() {
    return "localhost";
}

const char* getDatabaseName() {
    return "my_database";
}

const char* getDatabaseUser() {
    return "db_user";
}

const char* getDatabasePassword() {
    return "db_password";
}

int main() {
    printf("%s\n", getDatabaseConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}