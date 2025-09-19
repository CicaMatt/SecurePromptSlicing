#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} Payload;

double temperature_for_location(Payload payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *server = "localhost";
    const char *user = "root"; 
    const char *password = "";  /* set me first */
    const char *database = "Sensor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             payload.latitude, payload.longitude, payload.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    double temperature = 0.0;
    while ((row = mysql_fetch_row(res))) {
        if (row[0]) {
            temperature = atof(row[0]);
            break; // Assuming only one match
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-05"};
    double temp = temperature_for_location(payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}


To compile and run this code, you need MySQL client library installed:

1. Install MySQL development package (on Debian-based systems):
   
   sudo apt-get install libmysqlclient-dev
   

2. Compile the program with:
   
   gcc -o temperature_example your_source_file.c $(mysql_config --cflags --libs)
   

3. Run it using:
   
   ./temperature_example
    

Ensure that the MySQL server is running and you have a database named `Sensor` with a table `readings`, which has columns `latitude`, `longitude`, `date`, and `temperature`. Adjust user credentials as necessary.