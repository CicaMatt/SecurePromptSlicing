#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int is_moderator(const char* username) {
    const char* host = getenv("DB_HOST");
    const char* port = getenv("DB_PORT");
    const char* dbname = getenv("DB_NAME");
    const char* user = getenv("DB_USER");
    const char* password = getenv("DB_PASS");

    if (!host || !port || !dbname || !user || !password) {
        fprintf(stderr, "Database credentials not set in environment variables.\n");
        return 0;
    }

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo), "host=%s port=%s dbname=%s user=%s password=%s",
             host, port, dbname, user, password);

    PGconn* conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return 0;
    }

    char query[128];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s';", username);

    PGresult* res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 0;
    }

    int is_mod = 0;
    if (PQntuples(res) > 0 && strcmp(PQgetvalue(res, 0, 0), "t") == 0) {
        is_mod = 1;
    }

    PQclear(res);
    PQfinish(conn);

    return is_mod;
}

int main() {
    const char* username = "testuser";
    if (is_moderator(username)) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
    return 0;
}