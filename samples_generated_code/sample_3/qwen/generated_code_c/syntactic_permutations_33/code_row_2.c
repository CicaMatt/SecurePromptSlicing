#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

const char *example_domain = "example.com";

int redirect_invalid_url(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *query = strchr(url, '?');
    if (query == NULL)
        return MHD_NO;

    query++; // Move past the '?'
    const char *domain_param = strstr(query, "url=");
    if (domain_param == NULL)
        return MHD_NO;

    domain_param += 4; // Move past "url="
    const char *end_of_url = strchr(domain_param, '&');
    size_t url_length = end_of_url ? (size_t)(end_of_url - domain_param) : strlen(domain_param);

    char domain[url_length + 1];
    strncpy(domain, domain_param, url_length);
    domain[url_length] = '\0';

    if (strstr(domain, example_domain)) {
        struct MHD_Response *response;
        response = MHD_create_response(302);
        MHD_add_response_header(response, "Location", domain);
        int ret = MHD_queue_response(connection, 302, response);
        MHD_destroy_response(response);
        return ret;
    } else {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen("Invalid URL"), (void *)"Invalid URL", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, 400, response);
        MHD_destroy_response(response);
        return ret;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &redirect_invalid_url, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for keypress

    MHD_stop_daemon(daemon);
    return 0;
}