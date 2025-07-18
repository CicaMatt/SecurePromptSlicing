#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bcrypt.h"
#include "sqlite3.h"


int main(void)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    /* Open database */
    rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
    }
    else
        fprintf(stdout, "Opened database successfully\n");

    /* Create SQL statement */
    char *sql = "CREATE TABLE users (username TEXT, password TEXT);";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
        fprintf(stdout, "Table created successfully\n");

    /* Insert data into table */
    char *username = get_input("Enter username: ");
    char *password = get_input("Enter password: ");

    char salt[16];
    bcrypt_gensalt(12, salt);

    char hash[64];
    bcrypt_hashpw(password, salt, hash);

    sql = sqlite3_mprintf("INSERT INTO users (username, password) VALUES ('%s', '%s');", username, hash);

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
        fprintf(stdout, "Records created successfully\n");

    /* Close database */
    sqlite3_close(db);
    return 0;
}

char *get_input(const char *prompt)
{
    size_t len = strlen(prompt) + 1;
    char *buffer = (char *)malloc(len * sizeof(char));
    printf("%s", prompt);
    scanf("%s", buffer);
    return buffer;
}