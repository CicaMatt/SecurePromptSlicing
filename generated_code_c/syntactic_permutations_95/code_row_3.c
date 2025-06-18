#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sqlite3.h>
    #define SQLITE_DB "mydb.db"
    void createTable(){
        sqlite3 *db;
        char *errMsg = 0;
        int rc = sqlite3_open(SQLITE_DB, &db);
        if (rc){
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return;
        }
        char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password BLOB)";
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK){
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
            return;
        }
        rc = sqlite3_close(db);
    }
    void registerUser(){
        sqlite3 *db;
        char *errMsg = 0;
        int rc = sqlite3_open(SQLITE_DB, &db);
        if (rc){
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return;
        }
        char username[1024];
        printf("Enter a unique username: ");
        scanf("%1023s", username);
        int salt = rand() % 9999 + 1;
        char hashedPassword[16] = {0};
        printf("Enter password: ");
        scanf("%15s", hashedPassword);
        //hash the password with salt and store in database
        char sql[256];
        sprintf(sql, "INSERT INTO users (username,password) VALUES('%s','%d%s')", username, salt, hashedPassword);
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK){
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
            return;
        }
        rc = sqlite3_close(db);
    }
    int main(){
        createTable();
        registerUser();
        return 0;
    }