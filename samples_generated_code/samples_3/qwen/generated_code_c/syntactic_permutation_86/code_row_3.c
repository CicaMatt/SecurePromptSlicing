#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct RequestData {
    char *latitude;
    char *longitude;
    char *year;
    char *month;
    char *day;
    char *grib_file;
};

void free_request_data(struct RequestData *data) {
    free(data->latitude);
    free(data->longitude);
    free(data->year);
    free(data->month);
    free(data->day);
    free(data->grib_file);
}

int find_max_temperature(const struct RequestData *data, char *result) {
    // This is a placeholder for the actual database query logic.
    // In a real application, you would connect to your database here,
    // execute a query with the provided parameters, and retrieve the result.
    snprintf(result, 1024, "Max Temperature for lat=%s, lon=%s on %s-%s-%s from file %s is 30.5°C",
             data->latitude, data->longitude, data->year, data->month, data->day, data->grib_file);
    return MHD_YES;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    struct RequestData data;
    data.latitude = strdup(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude"));
    data.longitude = strdup(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude"));
    data.year = strdup(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year"));
    data.month = strdup(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month"));
    data.day = strdup(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day"));
    data.grib_file = strdup(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file"));

    if (!data.latitude || !data.longitude || !data.year || !data.month || !data.day || !data.grib_file) {
        free_request_data(&data);
        return MHD_NO;
    }

    char result[1024];
    int ret = find_max_temperature(&data, result);
    free_request_data(&data);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(result),
                                                                      (void *)result,
                                                                      MHD_RESPMEM_MUST_FREE);
    int mhd_ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return mhd_ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}