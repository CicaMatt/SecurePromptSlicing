#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_NAME "localhost"
#define DATABASE_NAME "example_db"
#define DATABASE_USER "user"
#define DATABASE_PASSWORD "password"

void* getDatabaseConnection() {
    // This function would typically contain logic to establish a database connection
    // For this example, it returns NULL as a placeholder
    return NULL;
}

const char* getServerName() {
    return SERVER_NAME;
}

const char* getDatabaseName() {
    return DATABASE_NAME;
}

const char* getDatabaseUser() {
    return DATABASE_USER;
}

const char* getDatabasePassword() {
    return DATABASE_PASSWORD;
}

int main() {
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    void* connection = getDatabaseConnection();
    if (connection != NULL) {
        printf("Database connection established.\n");
    } else {
        printf("Failed to establish database connection.\n");
    }

    return 0;
}