#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *payload;
};

void free_connection_info(void *coninfo_cls) {
    struct connection_info_struct *cis = coninfo_cls;
    free(cis->payload);
    free(cis);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api") != 0)
        return MHD_NO;

    struct connection_info_struct *cis;
    const char* payload = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");

    if (*con_cls == NULL) {
        cis = malloc(sizeof(struct connection_info_struct));
        if (cis == NULL)
            return MHD_NO;
        cis->payload = strdup(payload);
        *con_cls = cis;

        return MHD_YES;
    }

    cis = *con_cls;

    const char* response = "Not Found";
    int ret;

    if (cis->payload != NULL) {
        // Assuming payload is a JSON string and we are looking for "name": "value"
        char name_value[128];
        snprintf(name_value, sizeof(name_value), "{\"name\": \"%s\"}", cis->payload);
        response = name_value;
    }

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                          (void*)response,
                                                                          MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_NOTIFY_COMPLETED, free_connection_info,
                              NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Keep server running

    MHD_stop_daemon(daemon);
    return 0;
}