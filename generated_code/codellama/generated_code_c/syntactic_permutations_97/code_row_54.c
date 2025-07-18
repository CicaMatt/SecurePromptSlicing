#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

int main()
{
    char *username, *password, *firstname, *lastname, *email;
    printf("Username:");
    scanf("%s", username);
    printf("Password:");
    scanf("%s", password);
    printf("First Name:");
    scanf("%s", firstname);
    printf("Last Name:");
    scanf("%s", lastname);
    printf("Email Address:");
    scanf("%s", email);

    sqlite3 *db;
    char *sql = "SELECT username FROM user WHERE username=?";
    sqlite3_stmt *statement;
    int rc = 0;

    if (sqlite3_open("user.db", &db) != SQLITE_OK)
    {
        printf("Database failed to open!\n");
        return 1;
    }
    else
    {
        rc = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);
        if (rc != SQLITE_OK)
        {
            printf("SQL statement failed to prepare!\n");
            return 1;
        }
        else
        {
            sqlite3_bind_text(statement, 1, username, -1, NULL);
            while (sqlite3_step(statement) == SQLITE_ROW)
            {
                char *existing_username = (char *)sqlite3_column_text(statement, 0);
                if (strcmp(existing_username, username) == 0)
                {
                    printf("Username already exists!\n");
                    return 1;
                }
            }
        }
        sqlite3_finalize(statement);

        char *hashedPassword = password_hash(password);
        sql = "INSERT INTO user (username, password, firstname, lastname, email) VALUES(?, ?, ?, ?, ?)";
        rc = sqlite3_prepare_v2(db, sql, -1, &statement, NULL);

        if (rc != SQLITE_OK)
        {
            printf("SQL statement failed to prepare!\n");
            return 1;
        }
        else
        {
            sqlite3_bind_text(statement, 1, username, -1, NULL);
            sqlite3_bind_text(statement, 2, hashedPassword, -1, NULL);
            sqlite3_bind_text(statement, 3, firstname, -1, NULL);
            sqlite3_bind_text(statement, 4, lastname, -1, NULL);
            sqlite3_bind_text(statement, 5, email, -1, NULL);

            if (sqlite3_step(statement) == SQLITE_DONE)
            {
                printf("Registration Successful!\n");
            }
        }
    }
    sqlite3_close(db);
}

char *password_hash(const char *password)
{
    const EVP_MD *digest = NULL;
    unsigned int md_len;
    unsigned char hash[EVP_MAX_MD_SIZE];
    char hex_hash[(EVP_MAX_MD_SIZE * 2) + 1];
    digest = EVP_sha512();
    if (!digest)
        return NULL;
    md_len = EVP_MD_size(digest);
    if (md_len > EVP_MAX_MD_SIZE)
        return NULL;

    EVP_Digest((const unsigned char *)password, strlen(password), hash, &md_len, digest, NULL);
    for (int i = 0; i < md_len; i++)
        sprintf(&hex_hash[i * 2], "%02x", hash[i]);
    hex_hash[md_len * 2] = '\0';
    return hex_hash;
}