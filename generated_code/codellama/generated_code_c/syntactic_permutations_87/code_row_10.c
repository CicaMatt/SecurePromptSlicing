#include <stdio.h>
#include <mysql/mysql.h>

int temperature_for_location(float lat, float lng, char *date) {
    int temperature = 0;

    // Connect to the database
    MYSQL mysql;
    mysql_init(&mysql);
    if (mysql_real_connect(&mysql, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        char query[256];
        sprintf(query, "SELECT temperature FROM table WHERE latitude = %f AND longitude = %f AND date = '%s'", lat, lng, date);
        if (mysql_query(&mysql, query)) {
            printf("MySQL query error : %s\n", mysql_error(&mysql));
        } else {
            MYSQL_RES *result = mysql_store_result(&mysql);
            if (result) {
                MYSQL_ROW row = mysql_fetch_row(result);
                if (row) {
                    temperature = atoi(row[0]);
                }
                mysql_free_result(result);
            }
        }
        mysql_close(&mysql);
    } else {
        printf("MySQL connection error : %s\n", mysql_error(&mysql));
    }

    return temperature;
}