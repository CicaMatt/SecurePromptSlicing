#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   for(int i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(void) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    const char* sql = 
        "CREATE TABLE IF NOT EXISTS users ("  \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
        "USERNAME TEXT NOT NULL,"             \
        "PASSWORD TEXT NOT NULL);";

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    char *insert_sql = malloc(256);
    snprintf(insert_sql, 256, "INSERT INTO users (USERNAME, PASSWORD) VALUES ('%s', '%s');", username, password);

    rc = sqlite3_exec(db, insert_sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Record created successfully\n");
    }

    free(insert_sql);
    sqlite3_close(db);

    return 0;
}