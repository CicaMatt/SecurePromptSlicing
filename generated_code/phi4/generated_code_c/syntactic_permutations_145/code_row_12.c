#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void buy_function(int quantity) {
    printf("Purchasing %d units of stock.\n", quantity);
    // Additional logic for purchasing can be added here.
}

int buy_stock(MYSQL *conn, int quantity) {
    char query[256];
    
    snprintf(query, sizeof(query), "INSERT INTO stocks (quantity) VALUES (%d);", quantity);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    } else {
        printf("Successfully inserted %d units into the database.\n", quantity);
    }

    buy_function(quantity);
    
    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0);
    
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }
    
    int quantity = 10; // This would typically come from a form input in a real scenario
    buy_stock(conn, quantity);

    mysql_close(conn);
    return EXIT_SUCCESS;
}