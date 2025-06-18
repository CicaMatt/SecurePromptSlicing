#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

void login(char *username, char *password){
    sqlite3 *db;
    if (sqlite3_open("test.db", &db) == SQLITE_OK) {
        char *err_msg = 0;
        char query[150];
        sprintf(query, "select password from users where username='%s'", username);
        sqlite3_exec(db, query, check_password, password, &err_msg);
    }
}

int check_password(void *data, int argc, char **argv, char **azColName){
    if(argc != 1)
        return 0;
    char *db_password = argv[0];
    char *user_password = data;
    if(strcmp(db_password, user_password) == 0)
        redirect_to_home();
}

void redirect_to_home(){
    //redirect code here
}