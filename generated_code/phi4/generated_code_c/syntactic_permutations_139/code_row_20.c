#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <libpq-fe.h>

int main() {
    const char *dbname = getenv("DB_NAME");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *host = getenv("DB_HOST");
    const int port = atoi(getenv("DB_PORT"));

    if (!dbname || !user || !password || !host || !getenv("DB_PORT")) {
        fprintf(stderr, "Database environment variables are not set properly.\n");
        return EXIT_FAILURE;
    }

    PGconn *conn = PQconnectdb(
        (char *)PQmakeConnectionInfo(
            user,
            host,
            port,
            dbname,
            password
        )
    );

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return EXIT_FAILURE;
    }

    PGresult *res = PQexec(conn, "SELECT is_moderator FROM users WHERE username = 'your_username'");

    if (PQstatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query execution failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        return EXIT_FAILURE;
    }

    int is_moderator = 0;
    if (PQntuples(res) > 0 && strcmp(PQgetvalue(res, 0, 0), "t") == 0) {
        is_moderator = 1;
    }

    printf("%s\n", is_moderator ? "True" : "False");

    PQclear(res);
    PQfinish(conn);

    return EXIT_SUCCESS;
}


**Note**: You must link this code with the PostgreSQL client library during compilation. For example:

On Linux:

gcc -o check_moderator check_moderator.c -lpq


On Windows, ensure you have the appropriate PostgreSQL client library and use a suitable command to compile with it.