#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"
#include <json/json.h>

int main() {
    MYSQL *conn;
    char *server = "localhost";
    char *user = "root";
    char *password = "your_password";
    char *database = "temperature_data";
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password,
                            database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char *sql = "SELECT MAX(Temperature) from temperature where year = ? and month = ? and day = ? and latitude = ? and longitude = ? and grib_file = ?";
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, "%s\n", mysql_error(stmt));
        exit(1);
    }

    // bind parameters
    MYSQL_BIND params[6];
    memset(params, 0, sizeof(params));

    char year[25], month[25], day[25], latitude[25], longitude[25], grib_file[25];
    snprintf(year, sizeof(year), "2017");
    snprintf(month, sizeof(month), "11");
    snprintf(day, sizeof(day), "01");
    snprintf(latitude, sizeof(latitude), "34.56");
    snprintf(longitude, sizeof(longitude), "-78.90");
    snprintf(grib_file, sizeof(grib_file), "2017110100");

    params[0].buffer_type = MYSQL_TYPE_STRING;
    params[0].buffer = (void *)year;
    params[0].is_null = 0;
    params[0].length = strlen(year);

    params[1].buffer_type = MYSQL_TYPE_STRING;
    params[1].buffer = (void *)month;
    params[1].is_null = 0;
    params[1].length = strlen(month);

    params[2].buffer_type = MYSQL_TYPE_STRING;
    params[2].buffer = (void *)day;
    params[2].is_null = 0;
    params[2].length = strlen(day);

    params[3].buffer_type = MYSQL_TYPE_STRING;
    params[3].buffer = (void *)latitude;
    params[3].is_null = 0;
    params[3].length = strlen(latitude);

    params[4].buffer_type = MYSQL_TYPE_STRING;
    params[4].buffer = (void *)longitude;
    params[4].is_null = 0;
    params[4].length = strlen(longitude);

    params[5].buffer_type = MYSQL_TYPE_STRING;
    params[5].buffer = (void *)grib_file;
    params[5].is_null = 0;
    params[5].length = strlen(grib_file);

    if (mysql_stmt_bind_param(stmt, params)) {
        fprintf(stderr, "Parameter binding failed\n");
        exit(1);
    }

    // execute the query
    int ret = mysql_stmt_execute(stmt);
    if (ret != 0) {
        printf("Error executing statement: %s", mysql_stmt_error(stmt));
        return -1;
    }

    // process result set
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "Could not get the result set\n");
        exit(1);
    }

    int num_rows = mysql_num_rows(result);
    printf("Number of rows: %d\n", num_rows);

    // fetch the data and print it out
    char *max_temperature;
    while ((row = mysql_fetch_row(result))) {
        max_temperature = row[0];
        printf("%s", max_temperature);
    }

    mysql_free_result(result);
    mysql_stmt_close(stmt);
    return 0;
}

### Code Explanation:
- The code starts by including all the necessary libraries such as <stdio.h>, <stdlib.h>, <string.h>, "mysql/mysql.h" and <json/json.h>.
- Next, we define the main function and create a MYSQL pointer conn to store the connection object.
- We initialize the connection object by calling mysql_init(NULL).
- Then, we connect to the MySQL database by calling mysql_real_connect(conn, server, user, password,
                            database, 0, NULL, 0) and check for errors if any.
- Next, we define a SELECT query with placeholders for latitude; longitude; year; month; day and grib_file.
- We initialize a MYSQL_STMT pointer stmt to store the statement object and call mysql_stmt_init(conn).
- Then, we prepare the statement by calling mysql_stmt_prepare(stmt, sql, strlen(sql)) and check for errors if any.
- Next, we bind parameters by creating an array of MYSQL_BIND objects params[6] and assigning values to each parameter.
- Then, we call mysql_stmt_bind_param(stmt, params) to bind the parameters to the statement.
- We then execute the query by calling mysql_stmt_execute(stmt) and check for errors if any.
- Next, we create a MYSQL_RES pointer result to store the result set and call mysql_store_result(conn).
- Then, we print the number of rows in the result set using mysql_num_rows(result).
- We then fetch each row in the result set by calling mysql_fetch_row(result) and printing it out.
- Finally, we free the memory used by the result object by calling mysql_free_result(result) and close the statement object by calling mysql_stmt_close(stmt).