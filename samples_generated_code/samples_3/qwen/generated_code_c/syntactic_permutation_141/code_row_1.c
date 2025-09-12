#include <stdio.h>
#include <stdlib.h>

const char* getConnection() {
    return "Connection Established";
}

const char* getServerName() {
    return "localhost";
}

const char* getDatabaseName() {
    return "example_db";
}

const char* getDatabaseUser() {
    return "user";
}

const char* getDatabasePassword() {
    return "password";
}

int main() {
    printf("Connection: %s\n", getConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());
    return 0;
}