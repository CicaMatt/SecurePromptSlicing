#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libmicrohttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **ptr) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (strlen(url) == strlen("/api/temperature_for_location"))
        return MHD_YES;

    struct post_processor *postprocessor = *ptr;
    if (!postprocessor) {
        postprocessor = calloc(1, sizeof(struct post_processor));
        if (!postprocessor)
            return MHD_NO;

        postprocessor->kind = 0;
        *ptr = postprocessor;

        postprocessor->connection = connection;
        postprocessor->url = url;

        return MHD_YES;
    }

    if (postprocessor->kind == 1) {
        free(postprocessor);
        *ptr = NULL;

        MYSQL *conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "username", "password", "database", 0, NULL, 0)) {
            return MHD_NO;
        }

        char lat[64], lon[64], month[64], day[64], grib_file[256];
        sscanf(postprocessor->buffer, "latitude=%[^&]&longitude=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s", 
               lat, lon, month, day, grib_file);

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperatures WHERE latitude = '%s' AND longitude = '%s' "
                 "AND month = '%s' AND day = '%s' AND grib_file = '%s'", lat, lon, month, day, grib_file);

        if (mysql_query(conn, query)) {
            mysql_close(conn);
            return MHD_NO;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (!result) {
            mysql_close(conn);
            return MHD_NO;
        }

        MYSQL_ROW row = mysql_fetch_row(result);
        char *response;

        if (row && row[0]) {
            response = malloc(strlen("Temperature: ") + strlen(row[0]) + 1);
            sprintf(response, "Temperature: %s", row[0]);
        } else {
            response = strdup("No temperature data found.");
        }

        mysql_free_result(result);
        mysql_close(conn);

        struct MHD_Response *response_struct = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_struct);
        
        free(response);
        MHD_destroy_response(response_struct);

        return ret;
    }

    if (*upload_data_size > 0) {
        postprocessor->kind = 1;
        char *new_pos;

        new_pos = realloc(postprocessor->buffer,
                          postprocessor->length + *upload_data_size + 1);
        if (!new_pos)
            return MHD_NO;

        memcpy(new_pos + postprocessor->length, upload_data, *upload_data_size);
        *(new_pos + postprocessor->length + *upload_data_size) = '\0';

        postprocessor->buffer = new_pos;
        postprocessor->length += *upload_data_size;

        *upload_data_size = 0;
    }

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        fprintf(stderr, "Failed to initialize.\n");
        return 1;
    }

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}