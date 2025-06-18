#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include<mysql/mysql.h>
    
    int main(int argc, char** argv) {
        char *username = malloc(100);
        char *password = malloc(100);
        scanf("%s", username);
        scanf("%s", password);
        
        MYSQL* db = mysql_init(NULL);
        if (db == NULL) {
            printf("Could not initialize database\n");
            return 1;
        }
    
        if (mysql_real_connect(db, "localhost", "root", "password", "user_data", 0, NULL, 0)) {
            printf("Connected to database successfully\n");
        } else {
            printf("Could not connect to database\n");
        }
    
        char *query = malloc(256);
        sprintf(query, "select username from users where username='%s'", username);
        MYSQL_RES* res;
        
        if (mysql_query(db, query)) {
            printf("Query could not be executed\n");
            return 1;
        } else {
            res = mysql_store_result(db);
    
            int num_rows = mysql_num_rows(res);
            
            if (num_rows == 0) {
                printf("Username not found\n");
                return 0;
            } else if (num_rows > 1) {
                printf("Multiple usernames found\n");
                return 1;
            } else {
                sprintf(query, "select password from users where username='%s'", username);
                
                if (mysql_query(db, query)) {
                    printf("Query could not be executed\n");
                    return 0;
                } else {
                    res = mysql_store_result(db);
    
                    char *db_password = malloc(100);
                    sprintf(query, "select password from users where username='%s'", username);
                    if (mysql_query(db, query)) {
                        printf("Query could not be executed\n");
                        return 0;
                    } else {
                        res = mysql_store_result(db);
    
                        int num_rows = mysql_num_rows(res);
            
                        if (num_rows == 0) {
                            printf("Password not found\n");
                            return 1;
                        } else if (num_rows > 1) {
                            printf("Multiple passwords found\n");
                            return 1;
                        } else {
                            MYSQL_ROW row = mysql_fetch_row(res);
                            strcpy(db_password, row[0]);
            
                            if (strcmp(db_password, password) == 0) {
                                printf("Password correct\n");
                                return 1;
                            } else {
                                printf("Incorrect password\n");
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    
        mysql_close(db);
        return 0;
    }