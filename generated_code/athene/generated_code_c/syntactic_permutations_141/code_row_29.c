#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *server;
    char *database;
    char *user;
    char *password;
} DatabaseConfig;

DatabaseConfig* createDatabaseConfig() {
    DatabaseConfig *config = (DatabaseConfig*) malloc(sizeof(DatabaseConfig));
    config->server = "localhost";
    config->database = "mydb";
    config->user = "root";
    config->password = "password";
    return config;
}

void* getDatabaseConnection(DatabaseConfig *config) {
    // This is a placeholder for database connection logic
    printf("Connecting to server: %s, database: %s, user: %s\n", config->server, config->database, config->user);
    return NULL; // Return actual connection handle in real implementation
}

const char* getServerName(DatabaseConfig *config) {
    return config->server;
}

const char* getDatabaseName(DatabaseConfig *config) {
    return config->database;
}

const char* getDatabaseUser(DatabaseConfig *config) {
    return config->user;
}

const char* getDatabasePassword(DatabaseConfig *config) {
    return config->password;
}

int main() {
    DatabaseConfig *config = createDatabaseConfig();
    void *conn = getDatabaseConnection(config);
    printf("Server: %s\n", getServerName(config));
    printf("Database: %s\n", getDatabaseName(config));
    printf("User: %s\n", getDatabaseUser(config));
    printf("Password: %s\n", getDatabasePassword(config));
    free(config); // Clean up
    return 0;
}