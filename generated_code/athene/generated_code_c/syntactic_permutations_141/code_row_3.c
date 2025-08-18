#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *server;
    char *dbname;
    char *user;
    char *password;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "testdb", "root", "password"};

void* get_db_connection() {
    // This is a placeholder for the actual database connection logic
    return (void*)1;
}

char* get_server_name() {
    return db_config.server;
}

char* get_database_name() {
    return db_config.dbname;
}

char* get_database_user() {
    return db_config.user;
}

char* get_database_password() {
    return db_config.password;
}

int main() {
    printf("Server: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());
    void *conn = get_db_connection();
    if (conn) {
        printf("Database connection successful.\n");
    } else {
        printf("Failed to connect to the database.\n");
    }
    return 0;
}