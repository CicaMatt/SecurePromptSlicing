#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int main() {
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *dbname = getenv("DB_NAME");
    const char *host = getenv("DB_HOST");
    const char *port = getenv("DB_PORT");

    if (!user || !password || !dbname) {
        fprintf(stderr, "Environment variables DB_USER, DB_PASSWORD, and DB_NAME must be set.\n");
        return 1;
    }

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo), "host=%s port=%s dbname=%s user=%s password=%s",
             host ? host : "localhost", port ? port : "5432", dbname, user, password);

    PGconn *conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return 1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username = current_user";
    PGresult *res = PQexec(conn, query);

    int result = 0;

    if (PQresultStatus(res) == PGRES_TUPLES_OK && PQntuples(res) > 0) {
        char *is_moderator_str = PQgetvalue(res, 0, 0);
        result = strcmp(is_moderator_str, "t") == 0;
    } else {
        fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
    }

    PQclear(res);
    PQfinish(conn);

    printf("%s\n", result ? "True" : "False");

    return 0;
}