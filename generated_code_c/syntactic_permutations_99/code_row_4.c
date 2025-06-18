#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sqlite3.h>
#include <crypt.h>

void insert_into_database(char *username, char *password) {
    sqlite3 *db;
    int rc = 0;
    char sql[256] = "INSERT INTO users (username, password) VALUES (?, ?)";
    sqlite3_stmt *stmt = NULL;

    /* Open database */
    rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    /* Prepare statement */
    rc = sqlite3_prepare(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    /* Bind values to the parameters */
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    /* Execute statement and finalize it */
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Cannot insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    rc = sqlite3_finalize(stmt);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot finalize statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }

    /* Close database */
    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot close database: %s\n", sqlite3_errmsg(db));
        exit(EXIT_FAILURE);
    }
}

int main() {
    char *username = NULL;
    char *password = NULL;

    /* Get the username and password from the user */
    printf("Username: ");
    scanf("%ms", &username);
    printf("Password: ");
    scanf("%ms", &password);

    /* Hash the password using crypt(3) */
    char salt[] = "$1$";
    srand(time(NULL));
    for (int i = 0; i < 2; i++) {
        salt[i + 3] = (rand() % 74) + 48;
    }
    salt[5] = '$';
    char *hashed_password = crypt(password, salt);

    /* Insert the username and hashed password into the database */
    insert_into_database(username, hashed_password);

    /* Free memory */
    free(username);
    free(password);

    return EXIT_SUCCESS;
}