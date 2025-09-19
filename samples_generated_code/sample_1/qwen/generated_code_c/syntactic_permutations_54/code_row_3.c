#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"post\" action=\"/do_login\"><input type=\"text\" name=\"username\"><input type=\"password\" name=\"password\"><input type=\"submit\"></form></body></html>"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/login") == 0) {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(PAGE), (void*)PAGE, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    } else if (strcmp(method, "POST") == 0 && strcmp(url, "/do_login") == 0) {
        if (*con_cls == NULL) {
            *con_cls = malloc(*upload_data_size + 1);
            memcpy(*con_cls, upload_data, *upload_data_size);
            ((char *)(*con_cls))[*upload_data_size] = '\0';
            *upload_data_size = 0;
            return MHD_YES;
        } else {
            char *data = (char *)*con_cls;
            if (strstr(data, "username=admin") && strstr(data, "password=admin")) {
                struct MHD_Response *response;
                response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
                MHD_add_response_header(response, "Location", "/admin_page");
                MHD_destroy_response(response);
                free(data);
                return ret;
            } else {
                struct MHD_Response *response;
                response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*)"Invalid credentials", MHD_RESPMEM_PERSISTENT);
                int ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
                MHD_destroy_response(response);
                free(data);
                return ret;
            }
        }
    } else {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen("Not found"), (void*)"Not found", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}