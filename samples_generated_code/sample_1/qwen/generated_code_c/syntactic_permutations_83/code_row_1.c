#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    struct connection_info_struct *con_info = *con_cls;
    struct MHD_Response *response;
    int ret;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        con_info->connection = connection;
        con_info->memory = NULL;
        con_info->memory_size = 0;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (0 != *upload_data_size) {
        if (!aptr) aptr = 1;

        con_info->memory = realloc(con_info->memory, con_info->memory_size + *upload_data_size + 1);
        memcpy(&(con_info->memory[con_info->memory_size]), upload_data, *upload_data_size);
        con_info->memory_size += *upload_data_size;
        con_info->memory[con_info->memory_size] = '\0';
        *upload_data_size = 0;

        return MHD_YES;
    }

    char *name_value = strstr(con_info->memory, "name=");
    if (name_value != NULL) {
        name_value += strlen("name=");
        char *end_of_name = strchr(name_value, '&');
        if (end_of_name != NULL)
            *end_of_name = '\0';
        response = MHD_create_response_from_buffer(strlen(name_value), (void*) name_value, MHD_RESPMEM_MUST_COPY);
    } else {
        response = MHD_create_response_from_buffer(12, (void*)"Name not found", MHD_RESPMEM_PERSISTENT);
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free(con_info->memory);
    free(con_info);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}

struct connection_info_struct {
    struct MHD_Connection *connection;
    char *memory;
    size_t memory_size;
};