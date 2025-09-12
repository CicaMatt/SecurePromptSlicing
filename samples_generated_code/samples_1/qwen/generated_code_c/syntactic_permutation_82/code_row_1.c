#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *payload;
};

void free_connection_info(void *coninfo_cls) {
    struct ConnectionInfoStruct *con_info = coninfo_cls;
    if (NULL != con_info->payload)
        free(con_info->payload);
    free(con_info);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int aptr;
    struct ConnectionInfoStruct *con_info = *con_cls;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == con_info)
            return MHD_NO;
        con_info->payload = NULL;
        *con_cls = (void *)con_info;
        return MHD_YES;
    }

    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    if (0 != strcmp(url, "/api"))
        return MHD_NO;

    const char *name_value = strchr(url, '?');
    if (NULL == name_value) {
        return MHD_NO;
    }
    name_value++;

    con_info->payload = strdup(name_value);
    if (NULL == con_info->payload)
        return MHD_NO;

    aptr++;
    if (aptr < *upload_data_size) {
        aptr = *upload_data_size;
        return MHD_YES;
    }

    char *value = strstr(con_info->payload, "name=");
    if (NULL != value) {
        value += 5; // length of "name="
        char *end = strchr(value, '&');
        if (NULL == end)
            end = con_info->payload + strlen(con_info->payload);
        size_t len = end - value;
        char name[len + 1];
        strncpy(name, value, len);
        name[len] = '\0';

        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(name),
                                                  (void *)strdup(name),
                                                  MHD_RESPMEM_MUST_FREE);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
        return ret;
    }

    return MHD_NO;
}

int main(int argc, char *const *argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              free_connection_info, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("HTTP server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}