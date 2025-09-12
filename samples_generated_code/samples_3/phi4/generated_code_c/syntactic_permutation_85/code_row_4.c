#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationInfo;

double temperature_for_location(const char* payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    LocationInfo location;
    sscanf(payload, "{\"latitude\": %lf, \"longitude\": %lf, \"date\": \"%10[^\"]\"}", &location.latitude, &location.longitude, location.date);

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (!mysql_real_connect(conn, "localhost", "root", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
    
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             location.latitude, location.longitude, location.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(conn);
    double temperature = 0.0;
    
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (row[0]) {
            temperature = atof(row[0]);
        }
    }
    
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    const char* payload = "{\"latitude\": 40.7128, \"longitude\": -74.0060, \"date\": \"2023-10-01\"}";
    double temp = temperature_for_location(payload);
    
    printf("Temperature: %.2f\n", temp);

    return EXIT_SUCCESS;
}