#include <stdio.h>
#include <stdlib.h>

// Simulated database connection structure
typedef struct {
    char *server;
    char *database_name;
    char *user;
    char *password;
} DatabaseConnection;

DatabaseConnection create_db_connection() {
    DatabaseConnection conn;
    conn.server = "localhost";
    conn.database_name = "my_database";
    conn.user = "admin";
    conn.password = "securepassword123";
    return conn;
}

const char* get_server_name(DatabaseConnection conn) {
    return conn.server;
}

const char* get_database_name(DatabaseConnection conn) {
    return conn.database_name;
}

const char* get_user(DatabaseConnection conn) {
    return conn.user;
}

const char* get_password(DatabaseConnection conn) {
    return conn.password;
}

int main() {
    DatabaseConnection db_conn = create_db_connection();
    
    printf("Server: %s\n", get_server_name(db_conn));
    printf("Database Name: %s\n", get_database_name(db_conn));
    printf("User: %s\n", get_user(db_conn));
    printf("Password: %s\n", get_password(db_conn));

    return 0;
}