#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    char email[100];
    int email_exists = 0, unsubscribe_status = 0;
    char *query;
    MYSQL_RES *res_ptr;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn,
                            "localhost",
                            "root",
                            "",
                            "database",
                            0, NULL, 0)) {
        printf("%s\n", mysql_error(conn));
    }

    // Check if email exists in database
    printf("Enter your email: ");
    scanf("%s", email);
    query = (char *) malloc((strlen(email) + 100) * sizeof(char));
    sprintf(query, "SELECT email FROM subscribers WHERE email = '%s'", email);
    mysql_real_query(conn, query, strlen(query));
    res_ptr = mysql_store_result(conn);
    row = mysql_fetch_row(res_ptr);
    if (strcmp(row[0], email) == 0) {
        email_exists = 1;
    }

    // Unsubscribe email from database
    if (email_exists) {
        char *unsubscibe_query;
        unsubscibe_query = (char *) malloc((strlen(email) + 100) * sizeof(char));
        sprintf(unsubscibe_query, "CALL unsubscribe('%s')", email);
        mysql_real_query(conn, unsubscibe_query, strlen(unsubscibe_query));
    }

    // Check if unsubscribe is successful
    query = (char *) malloc((strlen(email) + 100) * sizeof(char));
    sprintf(query, "SELECT email FROM subscribers WHERE email = '%s'", email);
    mysql_real_query(conn, query, strlen(query));
    res_ptr = mysql_store_result(conn);
    row = mysql_fetch_row(res_ptr);
    if (strcmp(row[0], email) != 0) {
        unsubscribe_status = 1;
    }

    // Print result
    if (!email_exists) {
        printf("Email doesn't exist in database.\n");
    } else if (!unsubscribe_status) {
        printf("Unsubscribe failed\n");
    } else {
        printf("Unsubscribe successful\n");
    }

    mysql_free_result(res_ptr);
    mysql_close(conn);
    free(query);
}