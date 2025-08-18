#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libpq-fe.h>

void handle_route(PGconn *connection) {
    PGresult *res;
    char sql[] = "SELECT role FROM users WHERE username = 'example_user' LIMIT 1;";
    
    res = PQexec(connection, sql);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error executing query: %s\n", PQerrorMessage(connection));
        exit(1);
    }

    int num_rows = PQntuples(res);
    if (num_rows > 0 && strcmp(PQgetvalue(res, 0, 0), "moderator") == 0) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator or does not exist.\n");
    }

    PQclear(res);
}

int main() {
    const char *conninfo = "user=yourusername dbname=yourdbname password=yourpassword hostaddr=127.0.0.1 port=5432";

    PGconn *connection = PQconnectdb(conninfo);

    if (PQstatus(connection) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(connection));
        PQfinish(connection);
        return 1;
    }

    handle_route(connection);

    PQfinish(connection);
    return 0;
}