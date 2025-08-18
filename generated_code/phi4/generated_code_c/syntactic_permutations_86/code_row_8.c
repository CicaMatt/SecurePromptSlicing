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
    if (0 != strcmp(method, "POST")) return MHD_NO;

    int ret;
    struct MHD_Response *response;
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    // Extract POST data
    char *lat = NULL, *lon = NULL, *year = NULL, *month = NULL, 
         *day = NULL, *grib_file = NULL;

    if (*upload_data_size == 0) return MHD_YES;
    
    char *data_end = (char *) upload_data + *upload_data_size;
    for (; upload_data < data_end; upload_data++) {
        if (*upload_data == ';') {
            *upload_data = '\0';
        }
    }

    // Assuming input format: lat=XX.1234&lon=-XX.XXXX&year=YYYY&month=MM&day=DD&grib_file=file.grb
    for (char *ptr = upload_data; ptr < data_end;) {
        char *key, *value;
        key = strsep(&ptr, "=");
        value = strsep(&ptr, "&");

        if (strcmp(key, "lat") == 0) lat = strdup(value);
        else if (strcmp(key, "lon") == 0) lon = strdup(value);
        else if (strcmp(key, "year") == 0) year = strdup(value);
        else if (strcmp(key, "month") == 0) month = strdup(value);
        else if (strcmp(key, "day") == 0) day = strdup(value);
        else if (strcmp(key, "grib_file") == 0) grib_file = strdup(value);
    }

    // Connect to MySQL
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, "localhost", "user", "password",
                            "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        response = MHD_create_response_from_buffer(0, "", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    // Execute Query
    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperatures WHERE "
             "latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
             lat, lon, year, month, day, grib_file);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        response = MHD_create_response_from_buffer(0, "Database error", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
    } else {
        res = mysql_store_result(&conn);
        if (res) {
            row = mysql_fetch_row(res);
            char *max_temp_str = (row && row[0]) ? row[0] : "No data";
            response = MHD_create_response_from_buffer(strlen(max_temp_str), max_temp_str, MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
        } else {
            fprintf(stderr, "%s\n", mysql_error(&conn));
            response = MHD_create_response_from_buffer(0, "Database error", MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
        }
    }

    // Cleanup
    free(lat); 
    free(lon); 
    free(year); 
    free(month); 
    free(day); 
    free(grib_file);

    if (res) mysql_free_result(res);
    mysql_close(&conn);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT,
                              NULL, NULL, &answer_to_connection, NULL, 
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    
    getchar(); // Wait for Enter key press

    MHD_stop_daemon(daemon);
    return 0;
}


Make sure to link the required libraries (`libmicrohttpd` and `mysqlclient`) when compiling this program, e.g., using:

gcc -o server your_program.c $(pkg-config --cflags --libs libmicrohttpd) -lmysqlclient