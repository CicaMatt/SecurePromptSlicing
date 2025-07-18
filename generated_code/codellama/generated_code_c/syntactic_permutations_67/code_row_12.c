#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

int main(int argc, char** argv) {
    // Check for correct number of arguments
    if (argc != 2) {
        printf("Usage: %s <image_file>\n", argv[0]);
        return 1;
    }

    // Get the image file path and name from the command line argument
    char* imgFile = argv[1];

    // Connect to the MySQL database
    MYSQL conn;
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, "localhost", "username", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 1;
    }

    // Prepare SQL query to insert the image file into the database
    char sql[256];
    sprintf(sql, "INSERT INTO images (img) VALUES ('%s')", imgFile);

    // Execute the SQL query
    if (mysql_query(&conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 1;
    }

    // Print a success message
    printf("Image file %s successfully stored in the MySQL database.\n", imgFile);

    // Close the MySQL connection
    mysql_close(&conn);

    return 0;
}