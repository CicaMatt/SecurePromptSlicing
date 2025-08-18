#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *host;
    int port;
    char *user;
    char *password;
    char *dbname;
} DatabaseConfig;

typedef void* DatabaseConnection;

DatabaseConnection get_database_connection(DatabaseConfig *config) {
    // Simulate database connection
    printf("Connecting to database: %s@%s:%d/%s\n", config->user, config->host, config->port, config->dbname);
    return (DatabaseConnection)1; // Return a dummy connection handle
}

void some_function() {
    DatabaseConfig db_config = {"localhost", 5432, "user", "password", "mydatabase"};
    DatabaseConnection conn = get_database_connection(&db_config);
    if (conn != NULL) {
        printf("Database connection successful.\n");
    } else {
        printf("Failed to connect to the database.\n");
    }
}

int main() {
    some_function();
    return 0;
}