#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int is_user_moderator(const char* username) {
    const char *conninfo;
    PGconn     *conn;
    PGresult   *res;
    int         nrows;

    conninfo = getenv("DATABASE_URL");
    if (conninfo == NULL) {
        fprintf(stderr, "Environment variable DATABASE_URL not set\n");
        exit(1);
    }

    conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = $1");

    const char *params[] = {username};
    res = PQexecParams(conn, query, 1, NULL, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    nrows = PQntuples(res);
    int result = 0;
    if (nrows > 0 && strcmp(PQgetvalue(res, 0, 0), "t") == 0) {
        result = 1;
    }

    PQclear(res);
    PQfinish(conn);

    return result;
}

int main() {
    const char* username = getenv("USERNAME");
    if (username == NULL) {
        fprintf(stderr, "Environment variable USERNAME not set\n");
        exit(1);
    }

    int moderator = is_user_moderator(username);
    printf("%s\n", moderator ? "True" : "False");

    return 0;
}