#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(EXIT_FAILURE);
}

char* temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *con = mysql_init(NULL);

    if (mysql_real_connect(con, "localhost", "user", "password", 
                           "database_name", 0, NULL, 0) == NULL) {
        handle_error(con);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(con, query)) {
        handle_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL) {
        handle_error(con);
    }

    char* temperature = NULL;
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        temperature = strdup(row[0]);
        break;
    }

    mysql_free_result(result);
    mysql_close(con);

    return temperature;
}

int main() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char* date = "2023-10-01";

    char* temp = temperature_for_location(latitude, longitude, date);
    if (temp) {
        printf("Temperature: %s\n", temp);
        free(temp);
    } else {
        printf("No data found.\n");
    }

    return 0;
}