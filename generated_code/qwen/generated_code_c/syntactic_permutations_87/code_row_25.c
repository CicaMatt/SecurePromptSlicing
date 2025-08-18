#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "weather_db"

MYSQL *conn;

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    if (mysql_query(conn, "SELECT * FROM weather_data")) {
        finish_with_error(conn);
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL) {
        finish_with_error(conn);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) { 
        double lat = atof(row[0]);
        double lon = atof(row[1]);
        const char* dat = row[2];
        double temp = atof(row[3]);

        if (lat == latitude && lon == longitude && strcmp(dat, date) == 0) {
            mysql_free_result(result);
            return temp;
        }
    }

    mysql_free_result(result);
    return -999.0; // Return value indicating no data found
}

int main() {
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    } 

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        finish_with_error(conn);
    }

    double latitude = 37.7749;
    double longitude = -122.4194;
    const char* date = "2023-10-01";

    double temperature = temperature_for_location(latitude, longitude, date);

    if (temperature != -999.0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("No data found for the given location and date.\n");
    }

    mysql_close(conn);
    return 0;
}