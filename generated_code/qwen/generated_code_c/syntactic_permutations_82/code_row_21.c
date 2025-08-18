#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *name;
};

const char *get_name_from_url(const char *url) {
    const char *query = strchr(url, '?');
    if (query) {
        query++; // move past the '?'
        const char *name_prefix = "name=";
        if (strncmp(query, name_prefix, strlen(name_prefix)) == 0) {
            return query + strlen(name_prefix);
        }
    }
    return NULL;
}

void iterate_post(void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
                  const char *filename, const char *content_type,
                  const char *transfer_encoding, const char *data,
                  uint64_t off, size_t size) {
    struct ConnectionInfoStruct *con_info = coninfo_cls;
    if (0 == strcmp(key, "name")) {
        con_info->name = strndup(data, size);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (NULL == *con_cls) {
        struct ConnectionInfoStruct *con_info;
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == con_info)
            return MHD_NO;
        con_info->name = NULL;
        *con_cls = con_info;

        if (strcmp(method, "POST") == 0) {
            int ret;
            ret = MHD_post_process(connection, iterate_post, con_info,
                                   upload_data, *upload_data_size);
            if (!ret) {
                free(con_info->name);
                free(con_info);
                return MHD_NO;
            }
        }

        return MHD_YES;
    }

    struct ConnectionInfoStruct *con_info = *con_cls;

    if (strcmp(method, "GET") == 0 && strcmp(url, "/api") == 0) {
        const char *name = get_name_from_url(url);
        if (name) {
            con_info->name = strdup(name);
        }
    }

    int ret;
    struct MHD_Response *response;

    if (con_info->name) {
        response = MHD_create_response_from_buffer(strlen(con_info->name),
                                                  (void *)con_info->name,
                                                  MHD_RESPMEM_MUST_FREE);
    } else {
        const char *not_found_msg = "Name not found";
        response = MHD_create_response_from_buffer(strlen(not_found_msg),
                                                  (void *)not_found_msg,
                                                  MHD_RESPMEM_PERSISTENT);
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free(con_info->name);
    free(con_info);
    *con_cls = NULL;

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}