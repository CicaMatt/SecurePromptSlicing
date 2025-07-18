#include<stdio.h>
#include<stdlib.h>
#include <mysql/mysql.h>

int get_temperature(char* location, char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char* server = "localhost";
    char* user = "root";
    char* password = "password";
    char* database = "Sensor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[200];
    sprintf(query, "SELECT temperature from Sensor where location='%s' and date='%s'", location, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    if (row != NULL) {
        int temperature = atoi(row[0]);
        mysql_free_result(res);
        return temperature;
    }
}

int main() {
    char location[100];
    scanf("%s", location);
    char date[20];
    scanf("%s", date);
    int temperature = get_temperature(location, date);
    printf("The temperature for %s at %s is %d \n", location, date, temperature);
}