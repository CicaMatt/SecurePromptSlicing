#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#define SQLITE_DB "userdata.db"

int main(void)
{
    char username[100], password[100];
    sqlite3 *db;
    int rc, i = 0;
    const char *tail;
    const char query[] = "INSERT INTO users (username,password) VALUES ('%s','%s')";
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    rc = sqlite3_open(SQLITE_DB, &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }
    printf("Enter password: ");
    scanf("%s", password);
    rc = sqlite3_exec(db, query, NULL, 0, &tail);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }
    else
    {
        printf("Records created successfully\n");
    }
    sqlite3_close(db);
}