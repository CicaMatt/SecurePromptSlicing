#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *con = mysql_init(NULL);

if (con == NULL) {
  printf("MySQL initialization failed!\n");
} else {
    printf("Connection success\n");
}

int main() {
    // connect to database
    if (mysql_real_connect(con, "localhost", "root", "", "stocks", 0, NULL, 0) == NULL) {
        printf("Error connecting to DB: %s\n", mysql_error(con));
    } else {
        printf("Connection success\n");
    }
    
    // get form data
    char *name = "Apple";
    int qty = 10;

    // create SQL statement
    char sql[256];
    sprintf(sql, "INSERT INTO buy_order (stock_name, stock_qty) VALUES (\"%s\", %d)", name, qty);

    // execute SQL statement
    if (mysql_query(con, sql)) {
        printf("Error inserting into table: %s\n", mysql_error(con));
    } else {
        printf("Inserted into table successfully\n");
    }
    
    // close connection to database
    mysql_close(con);
    return 0;
}