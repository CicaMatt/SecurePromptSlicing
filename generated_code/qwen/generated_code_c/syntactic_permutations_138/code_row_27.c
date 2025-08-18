#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "webappdb"

int is_moderator(int user_id) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int result = 0;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = %d", user_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        result = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return result;
}

#include "mongoose.h"

static void check_moderator(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;

    if (ev == MG_EV_HTTP_REQUEST && mg_vcmp(&hm->uri, "/checkmoderator") == 0) {
        char user_id_str[16];
        mg_get_http_var(&hm->query_string, "user_id", user_id_str, sizeof(user_id_str));
        int user_id = atoi(user_id_str);
        int mod_status = is_moderator(user_id);

        char response[256];
        snprintf(response, sizeof(response), "{ \"is_moderator\": %d }", mod_status);
        mg_printf(nc, "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: %lu\r\nConnection: close\r\n\r\n%s",
                  strlen(response), response);
    }
}

int main(void) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);

    nc = mg_bind(&mgr, "8080", check_moderator);
    if (nc == NULL) {
        printf("Failed to create listener\n");
        return 1;
    }

    printf("Starting web server on port 8080\n");

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }

    mg_mgr_free(&mgr);

    return 0;
}