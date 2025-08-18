#include <stdio.h>
#include <string.h>

const char* getConnection() {
    return "Connection Established";
}

const char* getServerName() {
    return "example.server.com";
}

const char* getDatabaseName() {
    return "example_db";
}

const char* getDatabaseUser() {
    return "db_user";
}

const char* getDatabasePassword() {
    return "secure_password"; // In a real application, avoid hardcoding passwords
}

int main() {
    printf("Connection: %s\n", getConnection());
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}