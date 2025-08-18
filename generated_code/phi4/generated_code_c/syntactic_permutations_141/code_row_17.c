#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* host;
    int port;
} DatabaseConnection;

DatabaseConnection get_database_connection() {
    DatabaseConnection conn;
    conn.host = "localhost";
    conn.port = 5432; // Example: PostgreSQL default port
    return conn;
}

const char* get_server_name() {
    return "My Web Server";
}

void display_info() {
    printf("Server Name: %s\n", get_server_name());
    DatabaseConnection dbConn = get_database_connection();
    printf("Database Host: %s, Port: %d\n", dbConn.host, dbConn.port);
}

int main() {
    display_info();
    return 0;
}