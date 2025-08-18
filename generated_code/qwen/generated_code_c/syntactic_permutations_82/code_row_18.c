#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Payload {
    char *name;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    static int aptr;
    struct Payload *payload = cls;

    if (0 != strcmp(method, "POST"))
        return MHD_NO; // Method not allowed

    if (*con_cls == NULL) {
        *con_cls = connection;
        return MHD_YES;
    }

    if (aptr != *upload_data_size) {
        aptr = *upload_data_size;
        return MHD_YES;
    }

    struct Payload new_payload;
    char *name_key = "name=";
    char *name_start = strstr(upload_data, name_key);
    if (name_start != NULL) {
        name_start += strlen(name_key);
        char *name_end = strchr(name_start, '&');
        if (name_end != NULL)
            *name_end = '\0';
        new_payload.name = strdup(name_start);
    }

    const char *response;
    int response_size;
    if (new_payload.name) {
        response = new_payload.name;
        response_size = strlen(response);
    } else {
        response = "No name found";
        response_size = strlen(response);
    }

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_size, (void *)response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}