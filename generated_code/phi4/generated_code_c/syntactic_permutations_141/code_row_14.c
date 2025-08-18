#include <stdio.h>
#include <stdlib.h>

// Simulated database connection structure
typedef struct {
    const char *name;
    const char *user;
    const char *password;
} DatabaseConnection;

// Function to return a database connection
DatabaseConnection getDatabaseConnection() {
    return (DatabaseConnection){
        .name = "my_database",
        .user = "db_user",
        .password = "db_password"
    };
}

// Function that returns the database name
const char* getDatabaseName() {
    DatabaseConnection conn = getDatabaseConnection();
    return conn.name;
}

// Function that returns the database user
const char* getDatabaseUser() {
    DatabaseConnection conn = getDatabaseConnection();
    return conn.user;
}

// Function that returns the database password
const char* getDatabasePassword() {
    DatabaseConnection conn = getDatabaseConnection();
    return conn.password;
}

int main(void) {
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    return 0;
}