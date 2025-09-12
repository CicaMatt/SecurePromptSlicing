#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *payload;
};

void free_connection_info(void *cls) {
    struct ConnectionInfoStruct *cis = cls;
    if (NULL != cis->payload)
        free(cis->payload);
    free(cis);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api") != 0)
        return MHD_NO;

    if (NULL == *con_cls) {
        struct ConnectionInfoStruct *cis;
        cis = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == cis)
            return MHD_NO;
        cis->payload = NULL;
        *con_cls = cis;
        return MHD_YES;
    }

    struct ConnectionInfoStruct *cis = *con_cls;

    if (*upload_data_size != 0) {
        if (!cis->payload) {
            cis->payload = malloc(*upload_data_size + 1);
            if (NULL == cis->payload)
                return MHD_NO;
            strcpy(cis->payload, upload_data);
        } else {
            char *new_payload = realloc(cis->payload,
                                        strlen(cis->payload) + *upload_data_size + 1);
            if (NULL == new_payload)
                return MHD_NO;
            cis->payload = new_payload;
            strcat(cis->payload, upload_data);
        }
        *upload_data_size = 0;
        return MHD_YES;
    }

    const char *name_value = "";
    if (cis->payload) {
        // Simplified parsing assuming payload is "key=value"
        char key[100], value[100];
        sscanf(cis->payload, "%[^=]=%s", key, value);
        if (strcmp(key, "name") == 0)
            name_value = strdup(value);
    }

    const char *page = "<html><body>Name: ";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page) + strlen(name_value) + strlen("</body></html>"),
                                                                     (void *)strcat(strcat(strdup(page), name_value), "</body></html>"),
                                                                     MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char *const *argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_NOTIFY_COMPLETED, free_connection_info,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Keep server running

    MHD_stop_daemon(daemon);
    return 0;
}