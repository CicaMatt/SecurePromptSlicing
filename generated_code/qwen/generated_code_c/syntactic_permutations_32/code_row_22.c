#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain)) {
        return MHD_HTTP_SEE_OTHER;
    } else {
        return MHD_HTTP_BAD_REQUEST;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    char redirect_url[256];
    snprintf(redirect_url, sizeof(redirect_url), "http://example.com");

    int ret;
    struct MHD_Response *response;

    if (strstr(url, "/redirect/")) {
        const char *target_url = url + strlen("/redirect/");
        int status_code = redirect_invalid_url(target_url);

        if (status_code == MHD_HTTP_SEE_OTHER) {
            response = MHD_create_response(0);
            MHD_add_response_header(response, "Location", redirect_url);
        } else {
            response = MHD_create_response_from_buffer(strlen("Invalid URL"), 
                                                       (void*)"Invalid URL", 
                                                       MHD_RESPMEM_PERSISTENT);
        }

        ret = MHD_queue_response(connection, status_code, response);
        MHD_destroy_response(response);
    } else {
        response = MHD_create_response_from_buffer(strlen("Not Found"),
                                                   (void*)"Not Found",
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
    }

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}