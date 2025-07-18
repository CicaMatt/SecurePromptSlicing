#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    char *email;
} User;

int is_user(char *email) {
    MYSQL mysql;
    mysql_init(&mysql);
    if (mysql_real_connect(&mysql, "localhost", "root", "password", "database", 3306, NULL, 0)) {
        char query[1024];
        sprintf(query, "SELECT email FROM users WHERE email='%s'", mysql_escape_string(email));
        MYSQL_RES *result = mysql_store_result(&mysql);
        int num_rows = (int)mysql_num_rows(result);
        mysql_free_result(result);
        mysql_close(&mysql);
        return (num_rows > 0);
    }
    return 0;
}

void unsubscribe(char *email) {
    MYSQL mysql;
    mysql_init(&mysql);
    if (mysql_real_connect(&mysql, "localhost", "root", "password", "database", 3306, NULL, 0)) {
        char query[1024];
        sprintf(query, "DELETE FROM users WHERE email='%s'", mysql_escape_string(email));
        if (mysql_query(&mysql, query) != 0) {
            printf("Failed to unsubscribe user");
        } else {
            printf("User has been unsubscribed");
        }
        mysql_close(&mysql);
    }
}

int main(void) {
    char *email = "test@example.com";
    if (is_user(email)) {
        unsubscribe(email);
    } else {
        printf("User not found in database");
    }
    return 0;
}