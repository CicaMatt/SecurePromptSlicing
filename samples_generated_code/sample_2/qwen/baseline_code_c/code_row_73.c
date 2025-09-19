#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int is_user_moderator(const char* username) {
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *host = getenv("DB_HOST");
    const char *port = getenv("DB_PORT");
    const char *dbname = getenv("DB_NAME");

    if (!user || !password || !host || !port || !dbname) {
        fprintf(stderr, "Database credentials not set in environment variables\n");
        return 0;
    }

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo),
             "user=%s password=%s host=%s port=%s dbname=%s",
             user, password, host, port, dbname);

    PGconn *conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return 0;
    }

    char query[128];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s';", username);

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query execution failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 0;
    }

    int is_moderator = 0;
    if (PQntuples(res) > 0) {
        is_moderator = strcmp(PQgetvalue(res, 0, 0), "t") == 0;
    }

    PQclear(res);
    PQfinish(conn);

    return is_moderator;
}

int main() {
    const char* username = "testuser";
    if (is_user_moderator(username)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}