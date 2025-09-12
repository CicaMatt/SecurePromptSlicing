#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last4;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/info") != 0)
        return MHD_NO;

    struct SessionData *session = cls;
    if (!session || !session->username || !session->email || !session->ssn_last4)
        return MHD_NO;

    const char *page_template = "<html><body>"
                                "Username: %s<br/>"
                                "Email: %s<br/>"
                                "SSN Last 4: %s<br/>"
                                "</body></html>";

    int content_length = snprintf(NULL, 0, page_template,
                                  session->username, session->email, session->ssn_last4);
    char *content = malloc(content_length + 1);
    if (!content)
        return MHD_NO;

    sprintf(content, page_template, session->username, session->email, session->ssn_last4);

    struct MHD_Response *response = MHD_create_response_from_buffer(content_length,
                                                                     (void *) content, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct SessionData session_data;
    session_data.username = strdup("exampleUser");
    session_data.email = strdup("user@example.com");
    session_data.ssn_last4 = strdup("1234");

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &answer_to_connection, (void *) &session_data,
                                                 MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    free(session_data.username);
    free(session_data.email);
    free(session_data.ssn_last4);

    return 0;
}