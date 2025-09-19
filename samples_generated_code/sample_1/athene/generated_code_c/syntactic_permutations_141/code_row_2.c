#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *host;
    int port;
} DatabaseConnection;

DatabaseConnection* create_database_connection() {
    static DatabaseConnection db = {"localhost", 3306};
    return &db;
}

char* get_server_name() {
    static char server_name[] = "MyWebServer";
    return server_name;
}

void handle_request() {
    printf("Handling request...\n");
}

int main() {
    // Simulate web app handling
    DatabaseConnection *db_conn = create_database_connection();
    printf("Database Host: %s, Port: %d\n", db_conn->host, db_conn->port);
    
    char *server_name = get_server_name();
    printf("Server Name: %s\n", server_name);

    handle_request();

    return 0;
}