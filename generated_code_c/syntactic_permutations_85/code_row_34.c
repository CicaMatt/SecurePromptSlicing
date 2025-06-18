#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    // Include functions from the MySQL Connector/C
    #include "mysql.h"
    
    #define SERVER      "localhost"
    #define SOCKETT     "/run/mysqld/mysqld.sock"
    #define DATABASE    "your_database"
    #define USER        "your_user"
    #define PSWD        "your_password"
    
    // Define the structure for storing the temperature data
    struct temperature{
      int day;
      int month;
      int year;
      float temp;
    };
    
    // Function to connect to the database and get the temperature for a given date
    void temperature_for_location(int lat, int lon, int day, int month, int year){
        MYSQL *connect = NULL;
        MYSQL_RES *res = NULL;
        MYSQL_ROW row;
    
        char query[200] = {'\0'};
        sprintf(query, "SELECT * FROM your_table WHERE lat=%d AND lon=%d AND day=%d AND month=%d AND year=%d", lat, lon, day, month, year);
    
        connect = mysql_init(NULL);
    
        if(!mysql_real_connect(connect, SERVER, USER, PSWD, DATABASE, 0, SOCKETT, 0)){
            fprintf(stderr, "%s\n", mysql_error(connect));
            exit(1);
        }
    
        if (mysql_query(connect, query)) {
            fprintf(stderr, "%s\n", mysql_error(connect));
            exit(1);
        }
    
        res = mysql_use_result(connect);
    
        // Iterate through the results and print them
        while ((row = mysql_fetch_row(res)) != NULL) {
            struct temperature temp;
            temp.day = atoi(row[0]);
            temp.month = atoi(row[1]);
            temp.year = atoi(row[2]);
            temp.temp = atof(row[3]);
    
            printf("%d %d %d %.2f\n", temp.day, temp.month, temp.year, temp.temp);
        }
    }
    
    int main(int argc, char *argv[]) {
        if (argc != 6) {
            fprintf(stderr, "Usage: %s <lat> <lon> <day> <month> <year>\n", argv[0]);
            exit(1);
        }
    
        // Get the latitude and longitude from the command line arguments
        int lat = atoi(argv[1]);
        int lon = atoi(argv[2]);
    
        // Get the date from the command line arguments
        int day = atoi(argv[3]);
        int month = atoi(argv[4]);
        int year = atoi(argv[5]);
    
        temperature_for_location(lat, lon, day, month, year);
    }