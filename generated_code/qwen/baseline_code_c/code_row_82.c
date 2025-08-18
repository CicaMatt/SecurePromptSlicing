#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *payload;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        struct ConnectionInfoStruct *cis;
        cis = malloc(sizeof(struct ConnectionInfoStruct));
        if (cis == NULL)
            return MHD_NO;
        cis->payload = MHD_http_unescape_string(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload"));
        *con_cls = cis;
        return MHD_YES;
    }

    struct ConnectionInfoStruct *cis = *con_cls;

    const char *response = "";
    if (cis != NULL && cis->payload != NULL) {
        // Assuming payload is in the format "key1=value1&key2=value2"
        // and we are looking for a key named "name".
        char *token, *string;
        string = strdup(cis->payload);
        token = strtok(string, "&");
        while (token != NULL) {
            if (strstr(token, "name=") == token) {
                response = token + strlen("name=");
                break;
            }
            token = strtok(NULL, "&");
        }
        free(string);
    }

    int ret;
    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free(cis->payload);
    free(cis);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}