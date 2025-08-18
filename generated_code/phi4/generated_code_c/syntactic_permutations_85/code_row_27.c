#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_PAYLOAD_SIZE 256

void handle_request(const char *payload) {
    MYSQL conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

    char query[512];
    float latitude, longitude;
    int year, month, day;

    if (sscanf(payload, "%f,%f,%d-%d-%d", &latitude, &longitude, &year, &month, &day) != 5) {
        printf("Invalid payload format\n");
        return;
    }

    if ((conn = mysql_init(NULL)) == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(&conn, "localhost", "username", "password", "Sensor", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperature_data WHERE latitude = %f AND longitude = %f AND date = '%04d-%02d-%02d'", 
             latitude, longitude, year, month, day);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(&conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    char payload[MAX_PAYLOAD_SIZE];

    // Simulate receiving a payload
    strcpy(payload, "37.7749,-122.4194,2023-10-15");

    handle_request(payload);

    return 0;
}