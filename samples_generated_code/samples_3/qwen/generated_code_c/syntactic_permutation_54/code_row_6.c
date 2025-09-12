#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"post\" action=\"/do_login\"><input type=\"text\" name=\"username\" placeholder=\"Username\"><br><input type=\"password\" name=\"password\" placeholder=\"Password\"><br><input type=\"submit\" value=\"Login\"></form></body></html>"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0) {
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(PAGE), (void*) PAGE, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        static int aptr;
        const char *data;

        if (*upload_data_size != 0) {
            data = upload_data;
            while (aptr < *upload_data_size && data[aptr] != '=')
                aptr++;
            if (aptr >= *upload_data_size) {
                return MHD_NO;
            }
            const char* username_start = &data[aptr + 1];
            aptr += strlen(username_start) + 1;
            while (aptr < *upload_data_size && data[aptr] != '=')
                aptr++;
            if (aptr >= *upload_data_size) {
                return MHD_NO;
            }
            const char* password_start = &data[aptr + 1];

            if (strcmp(username_start, ADMIN_USERNAME) == 0 && strcmp(password_start, ADMIN_PASSWORD) == 0) {
                struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
                MHD_add_response_header(response, "Location", "/admin_page");
                MHD_destroy_response(response);
                return ret;
            }
        }

        *upload_data_size = 0;
        struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
        MHD_destroy_response(response);
        return ret;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}