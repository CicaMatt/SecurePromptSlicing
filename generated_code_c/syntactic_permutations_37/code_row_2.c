#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

MYSQL* mysql;
int main(void)
{
    int is_connected = 0;
    char *username = "root";
    char *password = "mypasswd";
    char *database = "login_db";
    int error = 0;

    mysql_init(&mysql);

    if (mysql) {
        is_connected = mysql_real_connect(mysql, database, username, password, 0, 0, 0, 0);
    }

    if (is_connected) {
        char *query = "SELECT * FROM login_table WHERE username=? AND password=?";
        MYSQL_STMT *stmt = mysql_stmt_init(mysql);
        int result;
        if (!stmt) {
            error = 1;
        } else {
            result = mysql_stmt_prepare(stmt, query, strlen(query));
            if (result) {
                error = 1;
            } else {
                MYSQL_BIND bind[2];
                char user[64], pass[64];
                memset(bind, 0, sizeof(bind));

                bind[0].buffer_type = MYSQL_TYPE_STRING;
                bind[0].buffer = (char*)user;
                bind[0].is_null = 0;
                bind[0].length = &user_len;

                bind[1].buffer_type = MYSQL_TYPE_STRING;
                bind[1].buffer = (char*)pass;
                bind[1].is_null = 0;
                bind[1].length = &pass_len;

                result = mysql_stmt_bind_param(stmt, bind);
                if (result) {
                    error = 1;
                } else {
                    memset(user, 0, sizeof(user));
                    memset(pass, 0, sizeof(pass));

                    strcpy(user, username);
                    strcpy(pass, password);

                    user_len = strlen(user);
                    pass_len = strlen(pass);

                    result = mysql_stmt_execute(stmt);
                    if (result) {
                        error = 1;
                    } else {
                        MYSQL_RES *res = mysql_store_result(&mysql);
                        MYSQL_ROW row;

                        while ((row = mysql_fetch_row(res))) {
                            if (strcmp(username, row[0]) == 0 && strcmp(password, row[1]) == 0) {
                                printf("Successfully logged in!\n");
                                error = 0;
                                break;
                            } else {
                                error = 1;
                            }
                        }
                    }
                }
            }
        }
    }
    
    if (error) {
        printf("Cannot login!\n");
    } else {
        printf("Internal Server Error\n");
    }

    mysql_stmt_close(stmt);
    mysql_close(&mysql);
}