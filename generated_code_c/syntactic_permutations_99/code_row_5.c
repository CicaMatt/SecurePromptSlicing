#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

void hash_password(char *pwd, char *hashed) {
    int i;
    for (i = 0; i < strlen(pwd); i++) {
        hashed[i] = pwd[i] ^ 29;
    }
}

int main() {
    sqlite3 *db;
    char sql[100];
    int rc;
    const char *data = "Callback function called";
    char name[50], password[50], hashed_password[50];

    printf("Enter username: ");
    scanf("%49s", name);
    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);
    sprintf(sql, "INSERT INTO users (name, password) VALUES ('%s', '%s')", name, hashed_password);

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_exec(db, sql, callback, (void *)data, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Records created successfully\n");
    }
    sqlite3_close(db);
    return 0;
}

int callback(void *data, int argc, char **argv, char **azColName) {
    printf("%s: ", (const char *)data);
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
}