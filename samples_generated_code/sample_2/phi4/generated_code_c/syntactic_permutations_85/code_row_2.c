#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format YYYY-MM-DD
} Payload;

float temperature_for_location(Payload payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];
    
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1.0; // Error case
    }

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM TemperatureData WHERE latitude = %f AND longitude = %f AND date = '%s'",
             payload.latitude, payload.longitude, payload.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0; // Error case
    }

    res = mysql_use_result(conn);

    float temperature = -1.0;
    while ((row = mysql_fetch_row(res))) {
        if (row[0]) {
            temperature = atof(row[0]);
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-01"};
    float temp = temperature_for_location(payload);
    if (temp != -1.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
    return 0;
}


Note: Ensure that the MySQL development libraries are installed and linked during compilation with `-lmysqlclient`. Adjust database connection parameters (`localhost`, `root`, `Sensor`) as needed.