#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_data {
    MYSQL *connection;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0) {
        return MHD_NO; // Only handle POST requests
    }

    int ret;
    struct connection_data *connection_state;

    if (*con_cls == NULL) {
        connection_state = malloc(sizeof(struct connection_data));
        if (!connection_state)
            return MHD_NO;

        connection_state->connection = mysql_init(NULL);
        if (!mysql_real_connect(connection_state->connection, "localhost", "user", "password",
                                "database_name", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(connection_state->connection));
            free(connection_state);
            return MHD_NO;
        }

        *con_cls = connection_state;
    } else {
        connection_state = (struct connection_data *)*con_cls;
    }

    if (*upload_data_size > 0) {
        // Process the input data
        char latitude[64], longitude[64], year[8], month[3], day[3], grib_file[128];
        sscanf(upload_data, "latitude=%63[^&]&longitude=%63[^&]&year=%7[^&]&month=%2[^&]&day=%2[^&]&grib_file=%127s",
               latitude, longitude, year, month, day, grib_file);

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperatures WHERE "
                 "latitude = '%s' AND longitude = '%s' AND year = %s AND "
                 "month = '%s' AND day = '%s' AND grib_file = '%s'",
                 latitude, longitude, year, month, day, grib_file);

        if (mysql_query(connection_state->connection, query)) {
            fprintf(stderr, "%s\n", mysql_error(connection_state->connection));
        } else {
            MYSQL_RES *result = mysql_store_result(connection_state->connection);
            if (!result) {
                fprintf(stderr, "%s\n", mysql_error(connection_state->connection));
            } else {
                MYSQL_ROW row = mysql_fetch_row(result);
                char *response;
                if (row && row[0]) {
                    snprintf(response, 1024, "Max Temperature: %s", row[0]);
                } else {
                    response = strdup("No data found.");
                }
                MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
                ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
                MHD_destroy_response(mhd_response);
                free(response);
                mysql_free_result(result);
            }
        }

        *upload_data_size = 0;
    } else {
        char *html_form =
            "<form method=\"POST\" enctype=\"application/x-www-form-urlencoded\">"
            "Latitude: <input type=\"text\" name=\"latitude\"><br>"
            "Longitude: <input type=\"text\" name=\"longitude\"><br>"
            "Year: <input type=\"text\" name=\"year\"><br>"
            "Month: <input type=\"text\" name=\"month\"><br>"
            "Day: <input type=\"text\" name=\"day\"><br>"
            "GRIB File: <input type=\"text\" name=\"grib_file\"><br>"
            "<button>Submit</button>"
            "</form>";
        MHD_Response *response = MHD_create_response_from_buffer(strlen(html_form), (void *)html_form, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);
    }

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}