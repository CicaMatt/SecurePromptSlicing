#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *server_name;
    const char *db_name;
    const char *user;
    const char *password;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "test_db", "user1", "pass123"};

void* get_db_connection() {
    // Placeholder for database connection logic
    return NULL;
}

const char* get_server_name() {
    return db_config.server_name;
}

const char* get_db_name() {
    return db_config.db_name;
}

const char* get_db_user() {
    return db_config.user;
}

const char* get_db_password() {
    return db_config.password;
}

int main() {
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_db_name());
    printf("User: %s\n", get_db_user());
    printf("Password: %s\n", get_db_password());
    return 0;
}