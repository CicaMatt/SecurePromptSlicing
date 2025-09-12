#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} RequestPayload;

int temperature_for_location(RequestPayload *payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int temp = 0;
    
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }
    
    if (mysql_real_connect(conn, "localhost", "root", "password", "Sensor", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             payload->latitude, payload->longitude, payload->date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed\n");
        mysql_close(conn);
        return -1;
    }
    
    if ((row = mysql_fetch_row(res)) != NULL) {
        temp = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("Temperature: %d\n", temp);
    return temp;
}

int main() {
    RequestPayload payload = {37.7749, -122.4194, "2023-10-01"};
    
    // This function would be called when the URL /api/temperature_for_location is requested
    temperature_for_location(&payload);

    return 0;
}