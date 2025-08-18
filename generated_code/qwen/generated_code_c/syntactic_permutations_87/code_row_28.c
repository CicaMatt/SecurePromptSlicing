#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "weather_data"

MYSQL *conn;

double get_temperature(double latitude, double longitude, const char *date) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[256];
    
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    result = mysql_store_result(conn);
    
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    row = mysql_fetch_row(result);
    if (row != NULL) {
        double temperature = atof(row[0]);
        mysql_free_result(result);
        return temperature;
    } else {
        mysql_free_result(result);
        return -1; // No data found
    }
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    conn = mysql_init(NULL);
    
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }
    
    double temperature = get_temperature(latitude, longitude, date);
    
    if (temperature != -1) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("No data found for the given location and date.\n");
    }
    
    mysql_close(conn);
}

int main() {
    // Example call to temperature_for_location
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char *date = "2023-10-01";
    
    temperature_for_location(latitude, longitude, date);
    
    return 0;
}