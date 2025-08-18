#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_request(const char *payload) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    char latitude[50];
    char longitude[50];
    char date[20];
    
    // Parse payload
    sscanf(payload, "{\"latitude\":\"%[^"]\",\"longitude\":\"%[^"]\",\"date\":\"%[^\"]\"}", latitude, longitude, date);

    // Initialize MySQL connection
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, "localhost", "user", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM sensor_data WHERE date = '%s'", date);

    // Execute the query
    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    res = mysql_use_result(&conn);
    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given date.\n");
    }
    
    // Cleanup
    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    const char *payload = "{\"latitude\":\"12.9716\",\"longitude\":\"77.5946\",\"date\":\"2023-10-01\"}";
    handle_request(payload);
    return 0;
}