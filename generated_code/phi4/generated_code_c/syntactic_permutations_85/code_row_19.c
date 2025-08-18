#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_api_request(const char *payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "username", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char latitude[50], longitude[50], date[20];
    
    // Assuming payload is in the format: {"latitude": "xx.xxxx", "longitude": "yy.yyyy", "date": "yyyy-mm-dd"}
    sscanf(payload, "{\"latitude\": \"%[^\\\"]\", \"longitude\": \"%[^\\\"]\", \"date\": \"%[^\"]\"}", latitude, longitude, date);

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM sensor_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", latitude, longitude, date);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    const char *payload = "{\"latitude\": \"40.7128\", \"longitude\": \"-74.0060\", \"date\": \"2023-10-01\"}";

    handle_api_request(payload);

    return 0;
}