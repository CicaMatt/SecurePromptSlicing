#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "user"
#define PASSWORD "password"
#define DATABASE "weather_db"

MYSQL *connection, conn;

int connect_to_database() {
    mysql_init(&conn);
    connection = mysql_real_connect(&conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0);
    if (connection == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }
    return 0;
}

void close_database_connection() {
    mysql_close(connection);
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    connect_to_database();
    
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE lat = %f AND lon = %f AND date = '%s'", 
             latitude, longitude, date);
    
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    if (mysql_query(connection, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        close_database_connection();
        return -1.0;
    }
    
    result = mysql_store_result(connection);
    
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        close_database_connection();
        return -1.0;
    }
    
    row = mysql_fetch_row(result);
    double temperature = -1.0;
    if (row != NULL) {
        temperature = atof(row[0]);
    }
    
    mysql_free_result(result);
    close_database_connection();
    
    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char *date = "2023-10-01"; // Example date
    
    double temperature = temperature_for_location(latitude, longitude, date);
    
    printf("Temperature: %.2f\n", temperature);
    
    return 0;
}