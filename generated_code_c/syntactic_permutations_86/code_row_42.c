#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to handle MySQL errors
void handle_error(MYSQL *con) {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(EXIT_FAILURE);
}

int main() {
    // Connection details for the MySQL server
    const char* host = "localhost";
    const char* user = "root";
    const char* passwd = "password1234";
    const char* db = "weather";
    const unsigned int port = 3306;

    // Create a MySQL object
    MYSQL *con = mysql_init(NULL);

    // Connect to the MySQL server
    if (!mysql_real_connect(con, host, user, passwd, db, port, NULL, 0)) {
        handle_error(con);
    }

    // SQL query for maximum temperature in a given location and date range
    const char* sql = "SELECT * FROM temperature WHERE latitude = @latitude AND longitude = @longitude AND year = @year AND month = @month ORDER BY temperature DESC LIMIT 1";

    // Prepare the SQL query
    MYSQL_STMT *stmt = mysql_stmt_init(con);
    if (!stmt) {
        handle_error(con);
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        handle_error(con);
    }

    // Bind the input parameters
    MYSQL_BIND bind[4];
    memset(bind, 0, sizeof(bind));

    char latitude[256] = "12.34";
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (void *)latitude;
    bind[0].is_null = 0;
    bind[0].length = &(bind[0].buffer_length);

    char longitude[256] = "13.45";
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (void *)longitude;
    bind[1].is_null = 0;
    bind[1].length = &(bind[1].buffer_length);

    int year = 2023;
    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = (void *)&year;
    bind[2].is_null = 0;
    bind[2].length = &(bind[2].buffer_length);

    int month = 12;
    bind[3].buffer_type = MYSQL_TYPE_LONG;
    bind[3].buffer = (void *)&month;
    bind[3].is_null = 0;
    bind[3].length = &(bind[3].buffer_length);

    if (mysql_stmt_bind_param(stmt, bind)) {
        handle_error(con);
    }

    // Execute the query
    if (mysql_stmt_execute(stmt)) {
        handle_error(con);
    }

    // Bind the output parameter
    MYSQL_BIND out_bind[1];
    memset(out_bind, 0, sizeof(out_bind));

    int temperature = 0;
    out_bind[0].buffer_type = MYSQL_TYPE_LONG;
    out_bind[0].buffer = (void *)&temperature;
    out_bind[0].is_null = 0;
    out_bind[0].length = &(out_bind[0].buffer_length);

    if (mysql_stmt_bind_result(stmt, out_bind)) {
        handle_error(con);
    }

    // Fetch the result
    mysql_stmt_store_result(stmt);
    mysql_stmt_fetch(stmt);

    // Print the output
    printf("Maximum temperature: %d\n", temperature);

    // Clean up
    mysql_stmt_free_result(stmt);
    mysql_stmt_close(stmt);
    mysql_close(con);

    return EXIT_SUCCESS;
}