#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "Sensor"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

char* get_temperature_for_date(const char* date) {
    char query[256];
    sprintf(query, "SELECT temperature FROM temperatures WHERE date = '%s'", date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return NULL;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) != NULL) {
        char* temperature = strdup(row[0]);
        mysql_free_result(res);
        return temperature;
    } else {
        mysql_free_result(res);
        return NULL;
    }
}

void temperature_for_location() {
    const char* date = "2023-10-15"; // Example date from payload

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char* temperature = get_temperature_for_date(date);

    if (temperature != NULL) {
        printf("Temperature for %s: %s\n", date, temperature);
        free(temperature);
    } else {
        printf("No temperature found for %s\n", date);
    }

    mysql_close(conn);
}

int main() {
    temperature_for_location();
    return 0;
}