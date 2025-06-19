#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "md5.h"

int main()
{
    // Open or create database
    sqlite3 *db;
    int rc = sqlite3_open("login.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        fprintf(stdout, "Opened database successfully\n");
    }

    // Create SQL statement
    char *sql = "INSERT INTO USERS (USERNAME, PASSWORD, LAST_NAME, EMAIL) VALUES ('%s', '%s', '%s', '%s');";
    char username[50];
    char password[50];
    char lastname[50];
    char email[50];

    printf("Enter a username: ");
    scanf("%s", username);

    printf("Enter a password: ");
    scanf("%s", password);

    // Hash password
    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, (unsigned char *)password, strlen(password));
    unsigned char hash[16];
    MD5_Final(hash, &md5);

    printf("Enter a last name: ");
    scanf("%s", lastname);

    printf("Enter an email address: ");
    scanf("%s", email);

    // Execute SQL statement
    sqlite3_stmt *stmt;
    char *message;
    rc = sqlite3_prepare(db, sql, -1, &stmt, 0);
    if (rc == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            message = "Registration successful";
            printf("%s\n", message);
        }

        sqlite3_finalize(stmt);
    }
    else
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    // Close database connection
    rc = sqlite3_close(db);
    if (rc)
    {
        fprintf(stderr, "Can't close database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        fprintf(stdout, "Closed database successfully\n");
    }

    return 0;
}