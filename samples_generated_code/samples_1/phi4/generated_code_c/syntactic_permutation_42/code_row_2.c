#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple HTTP server using libmicrohttpd
#include <microhttpd.h>

#define PORT 8888

typedef struct {
    char *email;
    char *ssn;
} SessionData;

SessionData session = { .email = "user@example.com", .ssn = "123-45-6789" };

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/info") == 0) {
        char response[1024];
        snprintf(response, sizeof(response),
                 "Email: %s\nSSN: %s", session.email, session.ssn);

        struct MHD_Response *response_struct = MHD_create_response_from_buffer(
            strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_struct);
        MHD_destroy_response(response_struct);
        
        return ret;
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(
        0, NULL, MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD,
                              PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar(); // Wait for enter key

    MHD_stop_daemon(daemon);
    return 0;
}


To compile and run this code, you need to have the `libmicrohttpd` library installed. Use the following command to compile:


gcc -o webserver webserver.c $(pkg-config --cflags --libs libmicrohttpd)
./webserver


This will start a simple HTTP server on port 8888 that responds with email and SSN when `/info` is accessed via a GET request.