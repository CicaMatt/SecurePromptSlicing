#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "password"
#define DB_NAME "mydb"
#define QUERY "SELECT * FROM users WHERE username='%s'"
int main(void) {
    MYSQL *conn = NULL;
    MYSQL_RES *res = NULL;
    MYSQL_ROW row;
    char query[1024];
    int retval, exists = 0;
    /* Initialize the MySQL library and establish a connection to the specified database */
    mysql_init(NULL);
    conn = mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DB_NAME, 3306, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    /* Create and execute the query to check whether the username exists in the database */
    sprintf(query, QUERY, "username");
    retval = mysql_real_query(conn, query, strlen(query));
    if (retval != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    /* Check whether the username exists in the database */
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    if (row != NULL) {
        exists = 1;
    }
    printf("Username exists: %d\n", exists);
    /* Clean up and close the connection to the database */
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}