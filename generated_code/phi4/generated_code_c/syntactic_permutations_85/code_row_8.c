#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} Payload;

float temperature_for_location(Payload payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    float temperature = 0.0f;
    
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "Sensor", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             payload.latitude, payload.longitude, payload.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res)) != NULL) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-05"};
    float temp = temperature_for_location(payload);
    if (temp != 0.0f) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Temperature data not found.\n");
    }
    return 0;
}
