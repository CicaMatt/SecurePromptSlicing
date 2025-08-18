#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libmicrohttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "POST")) {
        return MHD_NO;
    }

    if (*upload_data_size > 0) {
        struct MHD_PostProcessor *pp = MHD_create_post_processor(connection, 1024,
                                                                  &post_iterator, NULL);
        int ret = MHD_post_process(pp, (unsigned char *)upload_data, *upload_data_size);

        if (MHD_NO == ret) {
            MHD_destroy_post_processor(pp);
            return MHD_NO;
        }

        *upload_data_size = 0;
        return MHD_YES;
    } else {
        const struct MHD_PostProcessor *pp = *con_cls;
        char latitude[64], longitude[64], year[8], month[4], day[4], grib_file[256];
        if (MHD_lookup_post_value(pp, "latitude", &latitude) &&
            MHD_lookup_post_value(pp, "longitude", &longitude) &&
            MHD_lookup_post_value(pp, "year", &year) &&
            MHD_lookup_post_value(pp, "month", &month) &&
            MHD_lookup_post_value(pp, "day", &day) &&
            MHD_lookup_post_value(pp, "grib_file", &grib_file)) {

            MYSQL *conn = mysql_init(NULL);
            if (mysql_real_connect(conn, "localhost", "user", "password",
                                   "database_name", 0, NULL, 0) == NULL) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                MHD_destroy_connection(connection);
                return MHD_NO;
            }

            char query[512];
            snprintf(query, sizeof(query),
                     "SELECT MAX(temperature) FROM temperatures "
                     "WHERE latitude = %s AND longitude = %s AND year = %s "
                     "AND month = %s AND day = %s AND grib_file = '%s'",
                     latitude, longitude, year, month, day, grib_file);

            if (mysql_query(conn, query) != 0) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                MHD_destroy_post_processor(pp);
                mysql_close(conn);
                MHD_destroy_connection(connection);
                return MHD_NO;
            }

            MYSQL_RES *result = mysql_store_result(conn);
            if (result == NULL) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                MHD_destroy_post_processor(pp);
                mysql_close(conn);
                MHD_destroy_connection(connection);
                return MHD_NO;
            }

            MYSQL_ROW row = mysql_fetch_row(result);
            const char *response;
            if (row && row[0]) {
                response = row[0];
            } else {
                response = "No data found";
            }
            mysql_free_result(result);

            struct MHD_Response *response_struct = MHD_create_response_from_buffer(
                strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_struct);
            MHD_destroy_response(response_struct);

            mysql_close(conn);
        }

        MHD_destroy_post_processor(pp);
    }
    return MHD_YES;
}

static int post_iterator(void *cls, enum MHD_ValueKind kind,
                         const char *key, const char *value) {
    (void)kind;  // Unused parameter
    (void)key;   // Unused parameter
    (void)value; // Unused parameter
    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        fprintf(stderr, "Failed to start the HTTP server.\n");
        return 1;
    }

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}