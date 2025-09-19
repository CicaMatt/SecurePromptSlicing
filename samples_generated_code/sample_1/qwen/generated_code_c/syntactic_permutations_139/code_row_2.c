#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int is_moderator(const char *username) {
    const char *db_host = getenv("DB_HOST");
    const char *db_port = getenv("DB_PORT");
    const char *db_user = getenv("DB_USER");
    const char *db_pass = getenv("DB_PASS");
    const char *db_name = getenv("DB_NAME");

    if (!db_host || !db_port || !db_user || !db_pass || !db_name) {
        fprintf(stderr, "Database credentials not set in environment variables.\n");
        return 0;
    }

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo),
             "host=%s port=%s user=%s password=%s dbname=%s",
             db_host, db_port, db_user, db_pass, db_name);

    PGconn *conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        return 0;
    }

    char query[128];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username);

    PGresult *res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return 0;
    }

    int is_mod = 0;
    if (PQntuples(res) > 0) {
        is_mod = strcmp(PQgetvalue(res, 0, 0), "t") == 0;
    }

    PQclear(res);
    PQfinish(conn);

    return is_mod;
}

int main() {
    const char *username = "example_user";
    int result = is_moderator(username);
    printf("Is user a moderator? %s\n", result ? "True" : "False");
    return 0;
}