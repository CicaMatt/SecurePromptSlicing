// This code is to be run on Linux or macOS machines only.


// The standard library header files needed for this program.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Header file for the MySQL C API functions.
#include <mysql/mysql.h>

// Structure to hold all the necessary information for a connection.
typedef struct {
    char* host;
    int port;
    char* user;
    char* pass;
} db_creds_t;

// Function to connect to the MySQL database using the credentials provided.
MYSQL* connect_db(db_creds_t creds) {
    // Initialize a new connection handle.
    MYSQL* conn = mysql_init(NULL);

    // Attempt to connect to the database.
    if (!mysql_real_connect(conn, creds.host, creds.user, creds.pass, NULL, creds.port, NULL, 0)) {
        printf("Connection failed\n");
        return NULL;
    }

    // Return a pointer to the connection handle.
    return conn;
}

// Function to disconnect from the MySQL database and free any associated resources.
void disconnect_db(MYSQL* conn) {
    mysql_close(conn);
}

int main() {
    // Set up some variables for the credentials we will need later.
    db_creds_t creds;
    creds.host = "localhost";
    creds.port = 3306;
    creds.user = "root";
    creds.pass = "";

    // Create a connection to the database using the credentials we just set up.
    MYSQL* conn = connect_db(creds);
    if (conn == NULL) {
        printf("Failed to connect to the database\n");
        return 1;
    }

    // Set up a variable for the image file we want to read in.
    FILE* img_file = fopen("image.jpg", "rb");
    if (img_file == NULL) {
        printf("Failed to open the image file\n");
        disconnect_db(conn);
        return 1;
    }

    // Set up a variable for the SQL query we want to execute.
    char* sql = "INSERT INTO images (id, data) VALUES (NULL, ?)";

    // Create a prepared statement from the query we just set up.
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (!mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        printf("Failed to prepare the SQL statement\n");
        fclose(img_file);
        disconnect_db(conn);
        return 1;
    }

    // Set up a variable for the data we want to send.
    char* img_data = malloc(300000 * sizeof(char));
    if (img_data == NULL) {
        printf("Failed to allocate memory for the image\n");
        fclose(img_file);
        disconnect_db(conn);
        return 1;
    }

    // Read in the entire contents of the image file.
    int img_size = fread(img_data, sizeof(char), 300000, img_file);
    if (img_size == -1) {
        printf("Failed to read the image file\n");
        free(img_data);
        mysql_stmt_close(stmt);
        disconnect_db(conn);
        return 1;
    }

    // Send the data as a parameter to the prepared statement.
    MYSQL_BIND params[1];
    memset(params, 0, sizeof(params));
    params[0].buffer = img_data;
    params[0].buffer_length = img_size * sizeof(char);
    if (mysql_stmt_bind_param(stmt, params)) {
        printf("Failed to bind the parameters\n");
        free(img_data);
        mysql_stmt_close(stmt);
        disconnect_db(conn);
        return 1;
    }

    // Execute the prepared statement with our data as a parameter.
    if (mysql_stmt_execute(stmt)) {
        printf("Failed to execute the SQL statement\n");
        free(img_data);
        mysql_stmt_close(stmt);
        disconnect_db(conn);
        return 1;
    }

    // Close the prepared statement and free any associated resources.
    mysql_stmt_close(stmt);

    // Disconnect from the MySQL database and free any associated resources.
    disconnect_db(conn);

    // Free any remaining memory we allocated for our data.
    free(img_data);

    return 0;
}