#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *host;
    int port;
} DatabaseConnection;

DatabaseConnection* get_database_connection() {
    DatabaseConnection *conn = (DatabaseConnection*) malloc(sizeof(DatabaseConnection));
    conn->host = "localhost";
    conn->port = 5432;
    return conn;
}

char* get_server_name() {
    char *server_name = "MyWebServer";
    return server_name;
}

void handle_request() {
    DatabaseConnection *conn = get_database_connection();
    char *server_name = get_server_name();

    printf("Handling request with connection to %s:%d and server name %s\n", conn->host, conn->port, server_name);

    free(conn);
}

int main() {
    handle_request();
    return 0;
}