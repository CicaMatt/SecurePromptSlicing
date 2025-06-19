#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#define SQLITE_DB "database.db"
#define SHA256_HASH

/* This function hashes the password using sha-256*/
char *sha256(const char* password){
  /* code to hash the password */
}

int main(){
    sqlite3 *db;
    int rc = sqlite3_open(SQLITE_DB, &db);
    if (rc != SQLITE_OK) {
        printf("ERROR: Database connection failed\n");
        return 1;
    }
    char username[20];
    char password[256];
    char firstname[20];
    char lastname[20];
    char email[40];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter First Name: ");
    scanf("%s", firstname);
    printf("Enter Last Name: ");
    scanf("%s", lastname);
    printf("Enter Email: ");
    scanf("%s", email);

    char *hashed_password = sha256(password);
    char sql[1024];
    sprintf(sql, "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('%s', '%s', '%s', '%s', '%s')", username, hashed_password, firstname, lastname, email);
    rc = sqlite3_exec(db, sql, NULL, 0, NULL);

    if (rc == SQLITE_CONSTRAINT) {
        printf("Username already exists.\n");
        return 1;
    }

    printf("Registration Successful.\n");

    sqlite3_close(db);
    return 0;
}