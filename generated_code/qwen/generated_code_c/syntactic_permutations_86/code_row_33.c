#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888
#define GribFile "path_to_your_grib_file.grib2"

int find_max_temperature(double latitude, double longitude, int year, int month, int day, const char* grib_file) {
    // This is a placeholder function. In a real scenario, you would use a GRIB parsing library
    // to extract the temperature data from the GRIB file for the given location and time.
    // For demonstration purposes, we'll return a dummy value.
    return 25; // Example maximum temperature in Celsius
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api/temperature_for_location") != 0) {
        return MHD_NO;
    }

    const char* latitude_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char* longitude_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char* year_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    const char* month_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    const char* day_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    const char* grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!latitude_str || !longitude_str || !year_str || !month_str || !day_str || !grib_file) {
        return MHD_NO;
    }

    double latitude = atof(latitude_str);
    double longitude = atof(longitude_str);
    int year = atoi(year_str);
    int month = atoi(month_str);
    int day = atoi(day_str);

    int max_temperature = find_max_temperature(latitude, longitude, year, month, day, grib_file);

    char response[128];
    snprintf(response, sizeof(response), "{\"max_temperature\": %d}", max_temperature);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar(); // Wait for any input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}