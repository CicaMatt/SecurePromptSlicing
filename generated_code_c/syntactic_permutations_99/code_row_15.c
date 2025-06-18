#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <openssl/sha.h>
#include <sqlite3.h>
 
#define USERNAME_MAXLENGTH 20
#define PASSWORD_MAXLENGTH 20
#define MAX_PASSWORD_HASH_SIZE 65
 
int main() {
    sqlite3 *db; // SQLite database object
 
    char *zErrMsg = NULL;
    const char *sql;
    int rc;
 
    /* Open the database file */
    rc = sqlite3_open("login.sqlite", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }
 
    char username[USERNAME_MAXLENGTH];
    printf("Enter Username: ");
    scanf("%20s", username);
 
    char password[PASSWORD_MAXLENGTH];
    printf("Enter Password: ");
    scanf("%20s", password);
 
    /* Hash the password */
    unsigned char hashedPassword[MAX_PASSWORD_HASH_SIZE];
    SHA1((const unsigned char *)password, strlen(password), hashedPassword);
 
    /* Insert the username and password into the database */
    sql = "INSERT INTO LOGIN (USERNAME, PASSWORD) VALUES ('%s', '%s');";
    sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (zErrMsg != NULL) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        return -1;
    }
 
    /* Close the database */
    sqlite3_close(db);
 
    return 0;
}