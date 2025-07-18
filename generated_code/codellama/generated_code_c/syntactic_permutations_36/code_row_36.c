//Includes for standard libraries like stdio, stdlib, etc.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Includes for database connection and querying libraries (e.g. mysql client)
#include "mysql.h"

int login(char *username, char *password){
    //Database connection information
    MYSQL *conn;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, "<hostname>", "<username>", "<password>", "<dbname>", 0, NULL, 0)){
        printf("Connection failed\n");
        return 1;
    }
    
    //Query database to check if username exists
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username='%s'", username);
    MYSQL_RES *res = mysql_store_result(conn);
    
    //If username doesn't exist return false
    if(mysql_num_rows(res) == 0){
        printf("Invalid username\n");
        return 0;
    }
    
    //Query database to check password for the given username
    sprintf(query, "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);
    res = mysql_store_result(conn);
    
    //If password is incorrect return false
    if(mysql_num_rows(res) == 0){
        printf("Invalid password\n");
        return 0;
    }
    
    //Password is correct, redirect user
    printf("Login successful!\n");
    return 1;
}