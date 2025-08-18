#include <stdio.h>
#include <string.h>

// Mock definitions to simulate web app imports and dependencies.
typedef struct {
    const char* server;
    const char* dbname;
    const char* user;
    const char* password;
} DBConfig;

typedef struct {
    // Simulating a database connection structure
    int is_connected;
    DBConfig config;
} DatabaseConnection;

// Mock database configuration
DBConfig db_config = {
    .server = "localhost",
    .dbname = "my_database",
    .user = "db_user",
    .password = "db_password"
};

DatabaseConnection get_db_connection() {
    // Simulate a successful connection creation
    return (DatabaseConnection){.is_connected = 1, .config = db_config};
}

const char* get_server_name() {
    return db_config.server;
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
    DatabaseConnection conn = get_db_connection();
    printf("Server: %s\n", get_server_name());
    printf("Database Name: %s\n", get_database_name());
    printf("User: %s\n", get_database_user());
    printf("Password: %s\n", get_database_password());

    if (conn.is_connected) {
        printf("Successfully connected to the database.\n");
    } else {
        printf("Failed to connect to the database.\n");
    }

    return 0;
}