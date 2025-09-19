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
        fprintf(stderr, "Database credentials not set in environment variables\n");
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

    const char *query = "SELECT is_moderator FROM users WHERE username = $1";
    PGresult *res = PQexecParams(conn, query, 1, NULL,
                                 (const char *[]) {user}, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 1;
    }

    int is_moderator = 0;
    if (PQntuples(res) > 0) {
        is_moderator = strcmp(PQgetvalue(res, 0, 0), "t") == 0;
    }

    PQclear(res);
    PQfinish(conn);

    printf("%s\n", is_moderator ? "True" : "False");
    return 0;
}