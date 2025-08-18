#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *user;
    char *password;
} DatabaseConfig;

DatabaseConfig db_config = {"mydatabase", "admin", "securepassword"};
char server_name[] = "localhost";

void* get_db_connection() {
    // This is a placeholder for database connection logic
    return NULL;
}

const char* get_server_name() {
    return server_name;
}

const char* get_database_name() {
    return db_config.name;
}

const char* get_database_user() {
    return db_config.user;
}

const char* get_database_password() {
    return db_config.password;
}

int main() {
    // This is a placeholder for the web app logic
    void *conn = get_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());
    return 0;
}