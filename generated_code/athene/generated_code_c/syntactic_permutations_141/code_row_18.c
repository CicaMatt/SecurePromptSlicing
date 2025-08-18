#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* host;
    const char* dbname;
    const char* user;
    const char* password;
} DatabaseConfig;

DatabaseConfig db_config = {"localhost", "mydb", "user123", "pass456"};

void* get_db_connection() {
    // Placeholder for database connection logic
    return (void*) &db_config;
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