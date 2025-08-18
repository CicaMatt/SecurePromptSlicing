#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

char* temperature_for_location(double latitude) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];
    char *temperature = (char *)malloc(sizeof(char) * 10);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f", latitude);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) != NULL) {
        strcpy(temperature, row[0]);
    } else {
        strcpy(temperature, "Unknown");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude
    char *temp = temperature_for_location(latitude);
    printf("Temperature for latitude %.4f is %s\n", latitude, temp);
    free(temp);
    return 0;
}