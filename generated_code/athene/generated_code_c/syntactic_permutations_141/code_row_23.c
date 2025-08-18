#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *user;
    char *password;
} DatabaseConfig;

DatabaseConfig db_config = {"mydatabase", "admin", "secure_password"};

void *get_db_connection() {
    // Placeholder for actual database connection logic
    return (void *)1;
}

const char *get_server_name() {
    return "localhost";
}

const char *get_database_name() {
    return db_config.name;
}

const char *get_database_user() {
    return db_config.user;
}

const char *get_database_password() {
    return db_config.password;
}

int main() {
    void *conn = get_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());
    return 0;
}