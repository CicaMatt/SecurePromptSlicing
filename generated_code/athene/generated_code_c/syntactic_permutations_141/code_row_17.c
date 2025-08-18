#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *host;
    int port;
} DatabaseConnection;

DatabaseConnection* get_db_connection() {
    DatabaseConnection *conn = (DatabaseConnection*) malloc(sizeof(DatabaseConnection));
    conn->host = "localhost";
    conn->port = 3306;
    return conn;
}

char* get_server_name() {
    char *server_name = "MyWebAppServer";
    return server_name;
}

void some_function() {
    // Function body
}