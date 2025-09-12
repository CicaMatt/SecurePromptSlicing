#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int check_credentials(const char *name, const char *password) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE name = '%s' AND password = '%s';", name, password);

    int exists = 0;
    sqlite3_stmt *res;

    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc == SQLITE_ROW) {
        exists = 1;
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
    return exists;
}

void handle_login(const char *name, const char *password) {
    if (check_credentials(name, password)) {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Redirecting</title></head>");
        printf("<body>Redirecting to home page...");
        printf("<script>window.location.href='home.html';</script>");
        printf("</body></html>");
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><head><title>Error</title></head>");
        printf("<body>Login failed. <a href='login.html'>Try again</a>.");
        printf("</body></html>");
    }
}

int main() {
    char name[256];
    char password[256];

    printf("Content-Type: text/html\n\n");

    if (fgets(name, sizeof(name), stdin) != NULL && fgets(password, sizeof(password), stdin) != NULL) {
        name[strcspn(name, "\n")] = 0;
        password[strcspn(password, "\n")] = 0;

        handle_login(name, password);
    } else {
        printf("<html><head><title>Error</title></head>");
        printf("<body>Invalid input.</body></html>");
    }

    return 0;
}