#include <stdio.h>

typedef struct {
    const char* host;
    const char* dbname;
    const char* user;
    const char* password;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "mydatabase", "myuser", "mypassword"};

void *get_db_connection() {
    // This is a placeholder for actual database connection logic
    return NULL;
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