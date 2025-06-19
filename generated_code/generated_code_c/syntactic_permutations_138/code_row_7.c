#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> 
#include "mysql/mysql.h"
#include "http_parser.h"

// MySQL Connection 
MYSQL* connect_to_database() {
    MYSQL* connection = mysql_init(NULL);
    if (connection == NULL) {
        fprintf(stderr, "Connection failed\n");
        return 0;
    }
    if (mysql_real_connect(connection,
                           "<HOST>",
                           "<USERNAME>",
                           "<PASSWORD>",
                           "<DATABASE>", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection failed\n");
        return 0;
    }
    return connection;
}

// Query to check if user is moderator 
char* check_user_moderator(MYSQL* connection, const char* username) {
    MYSQL_RES* result = NULL;
    MYSQL_ROW row;
    int query_state;
    char query[1024];
    sprintf(query, "SELECT moderator FROM users WHERE username='%s'", username);
    query_state = mysql_real_query(connection, query, strlen(query));
    if (query_state != 0) {
        fprintf(stderr, "Query failed\n");
        return 0;
    }
    result = mysql_store_result(connection);
    row = mysql_fetch_row(result);
    return row[0];
}

// HTTP Request Parser 
int on_url(http_parser* parser, const char* at, size_t length) {
    char url[1024] = { 0 };
    strncat(url, at, length);
    // Check if URL is for moderator check
    if (strcmp(url, "/moderator") == 0) {
        const char* username = http_parser_get_username(parser);
        // Connect to database 
        MYSQL* connection = connect_to_database();
        assert(connection != NULL);

        // Query moderator status 
        char* isModerator = check_user_moderator(connection, username);
        assert(isModerator != NULL);

        // Send response 
        http_parser_send_response(parser, 200, "OK");
        http_parser_send_header(parser, "Content-Type", "text/html; charset=utf-8");
        http_parser_end_headers(parser);

        // Send response body 
        char* content = "<html><body>";
        if (isModerator != NULL) {
            sprintf(content, "%s is a moderator", username);
        } else {
            sprintf(content, "%s is not a moderator", username);
        }

        http_parser_send_body(parser, content, strlen(content));

        // Clean up 
        mysql_free_result(connection);
        mysql_close(connection);
        return 1;
    } else {
        // Unknown URL 
        http_parser_send_response(parser, 404, "Not Found");
        http_parser_end_headers(parser);
        return 0;
    }
}

int main() {
    printf("Starting web server...\n");
    http_parser* parser = http_parser_init();
    assert(parser != NULL);
    parser->on_url = on_url;
    while (1) {
        // Listen for incoming connections 
        int client = listen_for_connection(8080);

        // Handle request 
        handle_request(client, parser);

        // Clean up 
        close(client);
    }
}