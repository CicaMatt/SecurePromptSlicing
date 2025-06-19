#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    char* email;
} UnsubscribeRequest;

int delete_user(MYSQL *con, char* email) {
    if (mysql_query(con, "DELETE FROM users WHERE email = ") != 0) {
        return 1;
    }
    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        return 1;
    }
    int num_rows = mysql_num_rows(result);
    if (num_rows == 0) {
        mysql_free_result(result);
        return 2;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    printf("User %s unsubscribed from mailing list\n", email);
    mysql_free_result(result);
    return 0;
}

int main() {
    UnsubscribeRequest req;
    char *email = malloc(256);
    scanf("%255s", email);
    req.email = email;
    
    MYSQL *con = mysql_init(NULL);
    if (con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }
    
    if (mysql_real_connect(con, "localhost", "user", "password",
                           "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(con));
        return 1;
    }
    
    int result = delete_user(con, email);
    if (result == 2) {
        printf("User %s is not subscribed to the mailing list\n", req.email);
    } else if (result != 0) {
        fprintf(stderr, "Failed to unsubscribe user: %s\n", mysql_error(con));
    }
    
    mysql_close(con);
    return result;
}