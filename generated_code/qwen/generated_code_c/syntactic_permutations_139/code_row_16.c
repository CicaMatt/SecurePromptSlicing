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
        fprintf(stderr, "Environment variables not set\n");
        return 1;
    }

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo), "user=%s password=%s host=%s port=%s dbname=%s",
             user, password, host, port, dbname);

    PGconn *conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }

    const char *username = getenv("CHECK_USER");
    if (!username) {
        fprintf(stderr, "Environment variable CHECK_USER not set\n");
        PQfinish(conn);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    int is_moderator = 0;
    if (PQntuples(res) > 0) {
        is_moderator = strcmp(PQgetvalue(res, 0, 0), "true") == 0;
    }

    printf("%s\n", is_moderator ? "True" : "False");

    PQclear(res);
    PQfinish(conn);

    return 0;
}