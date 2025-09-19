#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];  // Format YYYY-MM-DD
} LocationRequest;

double temperature_for_location(LocationRequest request) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1.0;  // Error code
    }
    
    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return -1.0;  // Error code
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             request.latitude, request.longitude, request.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0;  // Error code
    }

    res = mysql_use_result(conn);

    double temperature = -1.0;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] != NULL) {
            temperature = atof(row[0]);
            break;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    LocationRequest request = {37.7749, -122.4194, "2023-10-01"};
    double temp = temperature_for_location(request);
    
    if (temp != -1.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
    
    return 0;
}


Note: Replace `"localhost"`, `"user"`, `"password"`, and `"database_name"` with your actual database connection details. Ensure the MySQL client library is installed and linked correctly when compiling this code.