#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_user"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"
#define MYSQL_HOST "127.0.0.1"

void handle_request(char *request) {
    double latitude, longitude;
    int year, month, day;
    char grib_file[100];
    
    sscanf(request, "latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%s",
           &latitude, &longitude, &year, &month, &day, grib_file);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    result = mysql_store_result(conn);
    if (result && mysql_num_rows(result) > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        printf("Maximum Temperature: %s\n", row[0]);
    } else {
        printf("No data found.\n");
    }

    mysql_free_result(result);
    mysql_close(conn);
}

int main() {
    // Simulate receiving a request (in a real web application, this would be handled by the web server)
    char *request = "latitude=37.7749&longitude=-122.4194&year=2023&month=10&day=5&grib_file=grib_data.grb";
    handle_request(request);
    return 0;
}