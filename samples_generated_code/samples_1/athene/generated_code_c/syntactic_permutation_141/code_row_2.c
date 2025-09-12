#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *host;
    int port;
} DatabaseConnection;

DatabaseConnection* get_database_connection() {
    DatabaseConnection *conn = (DatabaseConnection*)malloc(sizeof(DatabaseConnection));
    conn->host = "localhost";
    conn->port = 5432;
    return conn;
}

char* get_server_name() {
    char *server_name = "MyWebServer";
    return server_name;
}

void handle_request() {
    DatabaseConnection *db_conn = get_database_connection();
    printf("Connected to database at %s:%d\n", db_conn->host, db_conn->port);
    free(db_conn);

    char *server_name = get_server_name();
    printf("Request handled by server: %s\n", server_name);
}

int main() {
    handle_request();
    return 0;
}