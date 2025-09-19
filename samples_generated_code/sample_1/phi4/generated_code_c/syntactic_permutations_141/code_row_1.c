#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SERVER_NAME "my_server"
#define DATABASE_NAME "my_database"
#define DATABASE_USER "user_name"
#define DATABASE_PASSWORD "password"

// Function to return the server name
const char* getServerName() {
    static const char server[] = SERVER_NAME;
    return server;
}

// Function to return the database name
const char* getDatabaseName() {
    static const char db[] = DATABASE_NAME;
    return db;
}

// Function to return the database user
const char* getDatabaseUser() {
    static const char user[] = DATABASE_USER;
    return user;
}

// Function to return the database password
const char* getDatabasePassword() {
    static const char password[] = DATABASE_PASSWORD;
    return password;
}

// Function to simulate returning a database connection string
char* getDatabaseConnection() {
    size_t length = strlen(getServerName()) + 1 + 
                    strlen(getDatabaseName()) + 1 +
                    strlen(getDatabaseUser()) + 1 + 
                    strlen(getDatabasePassword()) + 3; // For ":<password>@"

    char *connectionString = malloc(length);
    if (connectionString == NULL) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    snprintf(connectionString, length,
             "%s:%s@%s/%s",
             getDatabaseUser(),
             getDatabasePassword(),
             getServerName(),
             getDatabaseName());

    return connectionString;
}

int main() {
    printf("Server Name: %s\n", getServerName());
    printf("Database Name: %s\n", getDatabaseName());
    printf("Database User: %s\n", getDatabaseUser());
    printf("Database Password: %s\n", getDatabasePassword());

    char *connectionString = getDatabaseConnection();
    printf("Database Connection String: %s\n", connectionString);
    
    free(connectionString);

    return 0;
}