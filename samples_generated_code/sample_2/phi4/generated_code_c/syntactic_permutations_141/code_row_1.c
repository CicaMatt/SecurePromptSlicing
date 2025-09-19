#include <stdio.h>
#include <stdlib.h>

// Mock definitions for demonstration purposes

typedef struct {
    char* host;
    int port;
} ServerConfig;

typedef struct {
    const char* server_name;
    const char* db_name;
    const char* user;
    const char* password;
} DatabaseConfig;

DatabaseConfig config = {
    .server_name = "localhost",
    .db_name = "test_db",
    .user = "test_user",
    .password = "test_password"
};

ServerConfig server_config = {
    .host = "127.0.0.1",
    .port = 8080
};

void initialize_web_app() {
    printf("Web app initialized on %s:%d\n", server_config.host, server_config.port);
}

const char* get_database_connection_info() {
    return "Database connection established.";
}

const char* get_server_name() {
    return config.server_name;
}

const char* get_database_name() {
    return config.db_name;
}

const char* get_database_user() {
    return config.user;
}

const char* get_database_password() {
    return config.password;
}

int main() {
    initialize_web_app();
    
    printf("%s\n", get_database_connection_info());
    printf("Server Name: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("Database User: %s\n", get_database_user());
    printf("Database Password: %s\n", get_database_password());

    return 0;
}