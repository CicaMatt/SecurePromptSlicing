#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *conn;

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

int temperature_for_location(double latitude, double longitude, const char* date) {
    int temp = -999; // Default value indicating error
    if (mysql_query(conn, "SELECT Temperature FROM Sensor WHERE Latitude=latitude AND Longitude=longitude AND Date=date")) {
        finish_with_error(conn);
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL) {
        finish_with_error(conn);
    }

    int num_fields = mysql_num_fields(result);

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) { 
        temp = atoi(row[0]);
    }

    mysql_free_result(result);
    return temp;
}

int main(int argc, char **argv) {
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    } 

    if (mysql_real_connect(conn, "localhost", "user", "password", 
            "Sensor", 0, NULL, 0) == NULL) {
        finish_with_error(conn);
    }

    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char* date = "2023-10-01"; // Example date

    int temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %d\n", temperature);

    mysql_close(conn);
    exit(0);
}