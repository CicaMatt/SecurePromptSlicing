#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *server;
    const char *database;
    const char *user;
    const char *password;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "mydb", "root", "pass123"};

void* create_db_connection() {
    // Placeholder for database connection logic
    return (void*)1;
}

const char* get_server_name() {
    return db_config.server;
}

const char* get_database_name() {
    return db_config.database;
}

const char* get_database_user() {
    return db_config.user;
}

const char* get_database_password() {
    return db_config.password;
}

int main() {
    void *conn = create_db_connection();
    printf("Server: %s\n", get_server_name());
    printf("Database: %s\n", get_database_name());
    printf("User: %s\n", get_database_user());
    printf("Password: %s\n", get_database_password());
    return 0;
}