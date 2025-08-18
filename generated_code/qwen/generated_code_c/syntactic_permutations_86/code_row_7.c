#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "username"
#define PASSWORD "password"
#define DATABASE "database_name"

void extractParameters(char *request, double *latitude, double *longitude, int *year, int *month, int *day, char *grib_file) {
    sscanf(request, "lat=%lf&lon=%lf&year=%d&month=%d&day=%d&grib_file=%s", latitude, longitude, year, month, day, grib_file);
}

double findMaxTemperature(double latitude, double longitude, int year, int month, int day, char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude = %lf AND longitude = %lf AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", 
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    double maxTemperature = -999.0;
    if ((row = mysql_fetch_row(res)) != NULL) {
        maxTemperature = atof(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return maxTemperature;
}

int main() {
    char request[] = "lat=34.0522&lon=-118.2437&year=2023&month=10&day=1&grib_file=example.grib";
    double latitude, longitude;
    int year, month, day;
    char grib_file[100];

    extractParameters(request, &latitude, &longitude, &year, &month, &day, grib_file);

    double maxTemperature = findMaxTemperature(latitude, longitude, year, month, day, grib_file);

    printf("The maximum temperature is: %lf\n", maxTemperature);

    return 0;
}