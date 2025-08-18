#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <sqlite3.h>

#define PORT 8888

static int handle_request(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/post") == 0 && strcmp(method, "POST") == 0) {
        static int aptr;
        const char *username = NULL;
        const char *message = NULL;

        struct MHD_PostProcessor *pp = (struct MHD_PostProcessor *)*con_cls;

        if (*upload_data_size != 0) {
            pp = MHD_create_post_processor(connection, 1024, pp);
            MHD_post_process(pp, upload_data, *upload_data_size);
            *upload_data_size = 0;
            *con_cls = pp;
            return MHD_YES;
        }

        username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
        message = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");

        sqlite3 *db;
        if (sqlite3_open("messages.db", &db)) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return MHD_NO;
        }

        char sql[256];
        snprintf(sql, sizeof(sql), "INSERT INTO messages(username, message) VALUES('%s', '%s');",
                 username ? username : "", message ? message : "");

        if (sqlite3_exec(db, sql, 0, 0, 0)) {
            fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_close(db);

        const char *page = "<html><body>Message posted! <a href=\"/\">Back to main page</a></body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    } else if (strcmp(url, "/") == 0 && strcmp(method, "GET") == 0) {
        sqlite3 *db;
        if (sqlite3_open("messages.db", &db)) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return MHD_NO;
        }

        char sql[] = "SELECT username, message FROM messages ORDER BY id DESC;";
        sqlite3_stmt *res;

        if (sqlite3_prepare_v2(db, sql, -1, &res, 0) != SQLITE_OK) {
            fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
            return MHD_NO;
        }

        char response_buffer[4096] = "<html><body>";
        while (sqlite3_step(res) == SQLITE_ROW) {
            const char *username = (const char*)sqlite3_column_text(res, 0);
            const char *message = (const char*)sqlite3_column_text(res, 1);
            snprintf(response_buffer + strlen(response_buffer), sizeof(response_buffer) - strlen(response_buffer),
                     "<p><strong>%s:</strong> %s</p>", username, message);
        }
        sqlite3_finalize(res);

        strcat(response_buffer, "</body></html>");

        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_buffer), (void*)response_buffer, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        sqlite3_close(db);

        return ret;
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}