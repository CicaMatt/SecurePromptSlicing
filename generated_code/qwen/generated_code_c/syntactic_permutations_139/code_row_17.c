#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

int is_user_moderator(const char* username) {
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *hostaddr = getenv("DB_HOSTADDR");
    const char *port = getenv("DB_PORT");
    const char *dbname = getenv("DB_NAME");

    if (!user || !password || !hostaddr || !port || !dbname) {
        fprintf(stderr, "Database credentials not set in environment variables.\n");
        exit(1);
    }

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo),
             "user=%s password=%s hostaddr=%s port=%s dbname=%s",
             user, password, hostaddr, port, dbname);

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s';", username);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
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
    const char* username = "example_user";
    if (is_user_moderator(username)) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
    return 0;
}