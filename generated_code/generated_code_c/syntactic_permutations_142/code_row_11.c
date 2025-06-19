#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <mysql/mysql.h>

void unsubscribe(char *email) {
    MYSQL *conn;
    char query[256];
    sprintf(query, "DELETE FROM subscribers WHERE email = '%s'", email);
    mysql_query(conn, query);
}

int main() {
    char email[100];
    printf("Enter your email address: ");
    scanf("%99s", email);
    unsubscribe(email);
    return 0;
}