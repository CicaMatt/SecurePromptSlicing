#include <stdio.h>
#include <stdlib.h>

// Mock HTTP server and database libraries
typedef struct {
    char *host;
    int port;
} Server;

typedef struct {
    char *query;
} Database;

Server* create_server(const char *host, int port) {
    Server *server = (Server*)malloc(sizeof(Server));
    server->host = strdup(host);
    server->port = port;
    return server;
}

Database* connect_db() {
    Database *db = (Database*)malloc(sizeof(Database));
    db->query = NULL;
    return db;
}

void define_route(Server *server, const char *route, void (*handler)(void)) {
    printf("Route %s defined on server %s:%d\n", route, server->host, server->port);
    handler();
}

void execute_query(Database *db, const char *query) {
    db->query = strdup(query);
    printf("Executing query: %s\n", db->query);
}

void check_function() {
    Database *db = connect_db();
    execute_query(db, "SELECT * FROM users LIMIT 1");
    free(db);
}

int main() {
    Server *server = create_server("localhost", 8080);
    define_route(server, "/check", check_function);
    free(server);
    return 0;
}