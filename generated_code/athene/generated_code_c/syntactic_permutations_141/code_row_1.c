#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* host;
    const char* dbname;
    const char* user;
    const char* password;
} DatabaseConfig;

DatabaseConfig db_config = {
    .host = "localhost",
    .dbname = "mydatabase",
    .user = "myuser",
    .password = "mypassword"
};

void* create_db_connection() {
    // Placeholder for database connection logic
    return (void*)1;
}

const char* get_server_name() {
    return db_config.host;
}

const char* get_database_name() {
    return db_config.dbname;
}

const char* get_database_user() {
    return db_config.user;
}

const char* get_database_password() {
    return db_config.password;
}

int main() {
    void* db_conn = create_db_connection();
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());
    return 0;
}