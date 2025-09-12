#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PAGE "<html><body><form method=\"post\" action=\"/do_login\"><input type=\"text\" name=\"username\" placeholder=\"Username\" required/><br/><input type=\"password\" name=\"password\" placeholder=\"Password\" required/><br/><input type=\"submit\" value=\"Login\"/></form></body></html>"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "adminpass"

int login_handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method, const char *version,
                  const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(PAGE), (void*) PAGE, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int do_login_handler(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method, const char *version,
                     const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    struct connection_info_struct *con_info = *con_cls;

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (!con_info)
            return MHD_NO;
        con_info->memory = malloc(MEMORY_CHUNK_SIZE + 1);
        if (!con_info->memory) {
            free(con_info);
            return MHD_NO;
        }
        con_info->memory[0] = '\0';
        con_info->offset = 0;
        con_info->postprocessor = MHD_create_post_processor(connection, MEMORY_CHUNK_SIZE, iterate_post, (void*) con_info);
        if (!con_info->postprocessor) {
            free(con_info->memory);
            free(con_info);
            return MHD_NO;
        }
        *con_cls = (void*) con_info;

        return MHD_YES;
    }

    aptr = *upload_data_size;
    MHD_post_process(con_info->postprocessor, upload_data, *upload_data_size);
    *upload_data_size = 0;

    if (aptr > 0) {
        int ret;
        struct MHD_Response *response;

        const char* username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
        const char* password = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "password");

        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_SEE_OTHER, response);
            MHD_add_response_header(response, "Location", "/admin_page");
        } else {
            response = MHD_create_response_from_buffer(strlen("Invalid credentials"), (void*) "Invalid credentials", MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
        }

        MHD_destroy_post_processor(con_info->postprocessor);
        free(con_info->memory);
        free(con_info);

        MHD_destroy_response(response);
        return ret;
    }

    return MHD_YES;
}

int admin_page_handler(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method, const char *version,
                       const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int ret;
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen("<html><body><h1>Welcome to the Admin Page</h1></body></html>"), 
                                                                   "<html><body><h1>Welcome to the Admin Page</h1></body></html>", 
                                                                   MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &login_handler, NULL, MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL, 
                              MHD_OPTION_URI_LOG_CALLBACK, uri_log_callback, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}