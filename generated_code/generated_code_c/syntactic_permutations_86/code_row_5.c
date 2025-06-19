#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>

    // Replace with your MySQL credentials
    const char *server = "localhost";
    const char *username = "your_mysql_username";
    const char *password = "your_mysql_password";
    const char *database = "your_database";

    void connect_db(char **temperature);
    void get_max_temp(int latitude, int longitude, int year, int month, int day, char* grib_file, char** temperature);

    int main() {
        // Get latitude; longitude; year; month; day and grib_file from request
        int latitude = 1234567890;
        int longitude = 1234567890;
        int year = 2022;
        int month = 2;
        int day = 10;
        char* grib_file = "mygrib.grib";
        char *temperature;
        connect_db(&temperature);
        get_max_temp(latitude, longitude, year, month, day, grib_file, &temperature);
        printf("Maximum temperature: %s", temperature);
    }

    void connect_db(char **temperature) {
        MYSQL *conn;
        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, server, username, password, database, 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
        // Execute SQL query to find maximum temperature in the given latitude; longitude; year; month; day and grib_file
        char *query = "SELECT MAX(temp) FROM mytable WHERE latitude=1234567890 AND longitude=1234567890 AND year=2022 AND month=2 AND day=10 AND grib_file='mygrib.grib'";
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
        *temperature = mysql_fetch_field(result);
    }