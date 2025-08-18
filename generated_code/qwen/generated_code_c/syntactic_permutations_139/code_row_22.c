#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int main() {
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *host = getenv("DB_HOST");
    const char *port = getenv("DB_PORT");
    const char *dbname = getenv("DB_NAME");

    if (!user || !password || !host || !port || !dbname) {
        fprintf(stderr, "Environment variables not set.\n");
        return 1;
    }

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo), 
             "user=%s password=%s host=%s port=%s dbname=%s", 
             user, password, host, port, dbname);

    PGconn *conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }

    const char *query = "SELECT EXISTS(SELECT 1 FROM users WHERE username = 'your_username');";
    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query execution failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    int exists = strcmp(PQgetvalue(res, 0, 0), "t") == 0;

    printf("%s\n", exists ? "True" : "False");

    PQclear(res);
    PQfinish(conn);

    return 0;
}