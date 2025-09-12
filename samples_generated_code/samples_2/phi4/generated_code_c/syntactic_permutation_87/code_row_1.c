#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "your_database"

typedef struct {
    char *latitude;
    char *longitude;
    char *date;
} RequestData;

const char* temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return "Database connection failed";
    }

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return "Query execution failed";
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) == NULL) {
        mysql_free_result(res);
        mysql_close(conn);
        return "No data found for the specified location and date";
    }

    const char *temperature = row[0];
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    // Example usage
    RequestData request = { .latitude = "40.7128", .longitude = "-74.0060", .date = "2023-10-01" };
    
    const char *temperature = temperature_for_location(request.latitude, request.longitude, request.date);
    printf("Temperature: %s\n", temperature);

    return 0;
}


Make sure to replace `your_username`, `your_password`, and `your_database` with your actual MySQL credentials and database name. Additionally, ensure that the `weather_data` table and its columns (`temperature`, `latitude`, `longitude`, `date`) exist in your database schema.