#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int main() {
    const char *conninfo;
    PGconn     *conn;
    PGresult   *res;
    int         nFields;
    int         i, j;

    conninfo = getenv("DATABASE_URL");

    conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return 0;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username = $1";
    PGresult *preparedStatement = PQprepare(conn, "my_query", query, 1, NULL);

    if (PQresultStatus(preparedStatement) != PGRES_COMMAND_OK) {
        fprintf(stderr, "PREPARE failed: %s", PQerrorMessage(conn));
        PQclear(preparedStatement);
        PQfinish(conn);
        return 0;
    }
    PQclear(preparedStatement);

    const char *params[1];
    params[0] = getenv("USERNAME");

    res = PQexecPrepared(conn, "my_query", 1, params, NULL, NULL, 0);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 0;
    }

    int isModerator = 0;

    if (PQntuples(res) > 0) {
        char *value = PQgetvalue(res, 0, 0);
        if (strcmp(value, "t") == 0) {
            isModerator = 1;
        }
    }

    PQclear(res);
    PQfinish(conn);

    printf("%s\n", isModerator ? "True" : "False");

    return isModerator;
}