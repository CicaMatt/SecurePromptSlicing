#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

// Function prototype
void upload_image();

// Global variables
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *server = "localhost";
char *user = "root";
char *password = "root"; /* set password */
char *database = "image_uploader";

// Main function
int main() {
    int status = 0;

    // Initialize and connect to MySQL server
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        exit(1);
    }

    // Call upload_image() function
    upload_image();

    // Close connection
    mysql_close(conn);

    return 0;
}

// Function to upload image
void upload_image() {
    char *name;
    char *base64string;

    // Get file name and base64 string from user input
    printf("Enter image name: ");
    scanf("%s", name);
    printf("Enter base64 string: ");
    scanf("%s", base64string);

    // Insert values into database
    char *sql = "INSERT INTO images (name, base64) VALUES ('%s', '%s');";
    sprintf(sql, name, base64string);

    if (mysql_query(conn, sql)) {
        printf("Error: %s\n", mysql_error(conn));
    } else {
        printf("Image uploaded successfully!\n");
    }
}