#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

int main() {
    const char *username = getenv("DB_USERNAME");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_DATABASE");
    const char *host = "localhost";
    
    if (username == NULL || password == NULL || database == NULL) {
        fprintf(stderr, "Environment variables are not set.\n");
        return 1;
    }

    FILE *conn;
    char command[512];
    
#ifdef _WIN32
    snprintf(command, sizeof(command), "mysql --host=%s --user=%s --password=%s %s", host, username, password, database);
#else
    snprintf(command, sizeof(command), "mysql --host=%s --user=%s --password=%s %s -Nse 'SELECT COUNT(*) FROM user_roles WHERE role = \"moderator\" AND username = \"%s\";'",
             host, username, password, database, username);
#endif

    conn = popen(command, "r");
    if (conn == NULL) {
        perror("Failed to run command");
        return 1;
    }

    int result;
    fscanf(conn, "%d", &result);

    pclose(conn);

    printf(result > 0 ? "True\n" : "False\n");

    return 0;
}