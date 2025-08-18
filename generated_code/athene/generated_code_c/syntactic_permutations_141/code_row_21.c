#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* server;
    char* db_name;
    char* db_user;
    char* db_password;
} DatabaseConfig;

DatabaseConfig* create_database_config() {
    DatabaseConfig* config = (DatabaseConfig*)malloc(sizeof(DatabaseConfig));
    config->server = "localhost";
    config->db_name = "mydatabase";
    config->db_user = "root";
    config->db_password = "password";
    return config;
}

void* get_db_connection(DatabaseConfig* config) {
    // Placeholder for database connection logic
    printf("Connecting to %s:%s as user %s\n", config->server, config->db_name, config->db_user);
    return NULL; // Return a real connection handle in actual implementation
}

const char* get_server_name(DatabaseConfig* config) {
    return config->server;
}

const char* get_database_name(DatabaseConfig* config) {
    return config->db_name;
}

const char* get_database_user(DatabaseConfig* config) {
    return config->db_user;
}

const char* get_database_password(DatabaseConfig* config) {
    return config->db_password;
}

int main() {
    DatabaseConfig* db_config = create_database_config();
    void* conn = get_db_connection(db_config);
    printf("Server: %s\n", get_server_name(db_config));
    printf("Database: %s\n", get_database_name(db_config));
    printf("User: %s\n", get_database_user(db_config));
    printf("Password: %s\n", get_database_password(db_config));
    free(db_config);
    return 0;
}