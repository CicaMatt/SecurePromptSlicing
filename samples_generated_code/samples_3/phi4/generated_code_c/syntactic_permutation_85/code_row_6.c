#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} Payload;

Payload parse_payload(const char *payload) {
    Payload p;
    sscanf(payload, "{\"latitude\":%lf,\"longitude\":%lf,\"date\":\"%10[^"]\"}",
           &p.latitude, &p.longitude, p.date);
    return p;
}

void temperature_for_location() {
    const char *payload = "{\"latitude\":37.7749,\"longitude\":-122.4194,\"date\":\"2023-01-01\"}";
    
    Payload p = parse_payload(payload);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "Sensor", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM sensor_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             p.latitude, p.longitude, p.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        res = mysql_use_result(conn);
        
        while ((row = mysql_fetch_row(res))) {
            printf("Temperature: %s\n", row[0]);
        }
        
        mysql_free_result(res);
    }

    mysql_close(conn);
}

int main() {
    temperature_for_location();
    return 0;
}
