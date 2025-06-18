#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

// Function to connect and disconnect from the database
void db_connect(MYSQL *conn, char *host, char *user, char *password, char *dbname) {
    if (mysql_real_connect(conn, host, user, password, dbname, 0, NULL, 0))
        printf("Connection to database was successful.\n");
}

void db_disconnect(MYSQL *conn) {
    mysql_close(conn);
}

// Function to create and drop the table in the database
void db_create_table(MYSQL *conn) {
    char query[1024] = "CREATE TABLE stocks (stock_name VARCHAR(64), quantity INT)";
    if (mysql_query(conn, query)) {
        printf("Table creation failed\n");
    } else {
        printf("Table created successfully\n");
    }
}

void db_drop_table(MYSQL *conn) {
    char query[1024] = "DROP TABLE stocks";
    if (mysql_query(conn, query)) {
        printf("Table drop failed\n");
    } else {
        printf("Table dropped successfully\n");
    }
}

// Function to insert data into the database
void db_insert_data(MYSQL *conn) {
    char stock_name[64];
    int quantity;

    // Get user input for stock name and quantity
    printf("Enter stock name: ");
    scanf("%s", stock_name);
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    char query[1024] = "INSERT INTO stocks (stock_name, quantity) VALUES ";
    sprintf(query + strlen(query), "('%s', %d)", stock_name, quantity);

    if (mysql_query(conn, query)) {
        printf("Insertion failed\n");
    } else {
        printf("Data inserted successfully\n");
    }
}

// Function to view the data in the database
void db_view_data(MYSQL *conn) {
    char query[1024] = "SELECT * FROM stocks";
    if (mysql_query(conn, query)) {
        printf("Query failed\n");
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        int num_fields = mysql_num_fields(result);
        int num_rows = mysql_num_rows(result);

        // Print the column names
        for (int i = 0; i < num_fields; i++) {
            printf("%s\t", mysql_fetch_field(result)->name);
        }
        printf("\n");

        // Print the data in each row
        while ((row = mysql_fetch_row(result)) != NULL) {
            for (int i = 0; i < num_fields; i++) {
                printf("%s\t", row[i]);
            }
            printf("\n");
        }
    }
}

int main() {
    // Create a connection handle
    MYSQL *conn;
    conn = mysql_init(NULL);

    // Define the host, user, password, and database to connect to
    char *host = "localhost";
    char *user = "root";
    char *password = "password";
    char *dbname = "stocks";

    // Connect to the database
    db_connect(conn, host, user, password, dbname);

    // Create and drop the table in the database
    db_create_table(conn);
    db_drop_table(conn);

    // Insert data into the database
    db_insert_data(conn);

    // View the data in the database
    db_view_data(conn);

    // Disconnect from the database
    db_disconnect(conn);
    return 0;
}