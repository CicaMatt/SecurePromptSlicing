#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format YYYY-MM-DD
} RequestData;

int temperature_for_location(RequestData requestData, float *temperature) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "Sensor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'",
             requestData.latitude, requestData.longitude, requestData.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        *temperature = atof(row[0]);
    } else {
        *temperature = -999.9; // Indicating no data found
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}

int main() {
    RequestData requestData = {37.7749, -122.4194, "2023-10-01"};
    float temperature;

    if (temperature_for_location(requestData, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}