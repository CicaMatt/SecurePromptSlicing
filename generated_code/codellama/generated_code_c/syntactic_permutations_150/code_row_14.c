#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DBNAME "guestbook"

void post() {
    char username[256];
    char message[1024];
    MYSQL_ROW row;
    MYSQL_RES *res;
    MYSQL *connection, mysql;
    int state;
    printf("Content-type: text/html\n\n");
    if (mysql_init(&mysql) == NULL) {
        fprintf(stderr, "Failed to initialize\n");
        return 1;
    }
    connection = mysql_real_connect(&mysql, HOST, USERNAME, PASSWORD, DBNAME, 3306, NULL, 0);
    if (connection == NULL) {
        fprintf(stderr, "Failed to connect\n");
        return 1;
    } else {
        printf("Connected successfully\n");
    }
    mysql_query(connection, "insert into messages (username, message) values ('%s', '%s')", username, message);
    res = mysql_store_result(connection);
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\n", row[0]);
    }
    mysql_free_result(res);
    if (mysql_query(connection, "select * from messages order by id desc") == 0) {
        res = mysql_store_result(connection);
        while ((row = mysql_fetch_row(res)) != NULL) {
            printf("<p>%s: %s</p>\n", row[1], row[2]);
        }
    } else {
        fprintf(stderr, "Failed to execute query\n");
        return 1;
    }
    mysql_close(connection);
}