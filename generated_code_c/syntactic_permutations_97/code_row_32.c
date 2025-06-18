#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#define SQLITE_DB "./database.db"
#define PASSWORD_HASH "SHA256"
#define TABLE_NAME "users"
#define USERNAME_FIELD "username"
#define PASSWORD_FIELD "password"
#define FIRST_NAME_FIELD "firstName"
#define LAST_NAME_FIELD "lastName"
#define EMAIL_FIELD "email"
#define SQLITE_OK 0
int sqlite3_open(const char *filename, sqlite3 **db);
int sqlite3_close(sqlite3 *db);
static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
int main(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc, i, nCol;
    char *sql;
    const char* data = "Callback function called";
    /* Open database */
    rc = sqlite3_open(SQLITE_DB, &db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }else{
        fprintf(stdout, "Opened database successfully\n");
    }
    /* Create SQL statement */
    sql = "SELECT * from COMPANY";
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
    return 0;
}