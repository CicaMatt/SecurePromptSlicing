#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM measurements WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char latitude[] = "37.7749";
    char longitude[] = "-122.4194";
    char date[] = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}


Note: Make sure to replace `"localhost"`, `"user"`, and `"password"` with your actual database host, username, and password, respectively. Also, ensure the MySQL client library is installed and properly linked during compilation. You might need to compile this code using a command like:


gcc -o temperature_program your_code.c $(mysql_config --cflags --libs)