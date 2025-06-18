#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

void insert_user_message_in_db(char *name, char *message) {
    MYSQL conn;
    mysql_init(&conn);
    if(!mysql_real_connect(&conn, "localhost", "root", "password", "mydb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return;
    }
    char query[256] = "INSERT INTO message (username, message) VALUES ('";
    strcat(query, name);
    strcat(query, "', '");
    strcat(query, message);
    strcat(query, "');");
    mysql_query(&conn, query);
    mysql_close(&conn);
}

void display_messages() {
    MYSQL conn;
    mysql_init(&conn);
    if(!mysql_real_connect(&conn, "localhost", "root", "password", "mydb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return;
    }
    MYSQL_RES *result = mysql_query(&conn, "SELECT username, message FROM message ORDER BY id DESC LIMIT 10");
    MYSQL_ROW row;
    while((row = mysql_fetch_row(result))) {
        printf("%s: %s\n", row[0], row[1]);
    }
    mysql_free_result(result);
    mysql_close(&conn);
}