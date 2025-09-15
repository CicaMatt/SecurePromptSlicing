#include <stdio.h>
#include <stdlib.h>
#include "mongoose.h"

// Database connection settings (replace with actual credentials)
#define DB_HOST "localhost"
#define DB_USER "username"
#define DB_PASSWORD "password"
#define DB_NAME "database_name"

void handle_request(struct mg_connection *nc, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) ev_data;

        // Connect to the database
        MYSQL *conn;
        conn = mysql_init(NULL);
        
        if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
            mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to connect to database.\r\n");
        } else {
            // Execute a query
            if (mysql_query(conn, "SELECT * FROM table_name LIMIT 1;")) {
                mg_printf(nc, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to execute query.\r\n");
            } else {
                mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nQuery executed successfully.\r\n");

                // Close database connection
                mysql_close(conn);
            }
        }

        // Clean up
        if (conn) {
            mysql_free_result(conn);
        }
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "8080", handle_request);
    mg_set_protocol_http_websocket(nc);

    printf("Starting web server on port 8080...\n");
    while (1) {
        mg_mgr_poll(&mgr, 1000); // Poll every second
    }

    mg_mgr_free(&mgr);
    return 0;
}
