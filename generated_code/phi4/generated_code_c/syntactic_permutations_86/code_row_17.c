#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <httpd.h>
#include <http_config.h>
#include <http_protocol.h>
#include <apr_strings.h>

#define DEFAULT_PORT "8080"
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "weather_db"

typedef struct {
    char *latitude;
    char *longitude;
    int year;
    int month;
    int day;
    char *grib_file;
} RequestData;

static void handler(request_rec *r) {
    if (strcmp(r->handler, "temperature_for_location")) {
        return;
    }

    RequestData data = {0};

    const char *latitude = apr_table_get(r->headers_in, "Latitude");
    const char *longitude = apr_table_get(r->headers_in, "Longitude");
    const char *year_str = apr_table_get(r->headers_in, "Year");
    const char *month_str = apr_table_get(r->headers_in, "Month");
    const char *day_str = apr_table_get(r->headers_in, "Day");
    const char *grib_file = apr_table_get(r->headers_in, "GribFile");

    if (latitude && longitude && year_str && month_str && day_str && grib_file) {
        data.latitude = strdup(latitude);
        data.longitude = strdup(longitude);
        data.year = atoi(year_str);
        data.month = atoi(month_str);
        data.day = atoi(day_str);
        data.grib_file = strdup(grib_file);

        MYSQL *conn;
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
            fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
            return;
        }

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperature_data WHERE latitude = '%s' AND longitude = '%s' "
                 "AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
                 data.latitude, data.longitude, data.year, data.month, data.day, data.grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
            return;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            if (row && row[0]) {
                char response[256];
                snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
                ap_set_content_type(r, "application/json");
                ap_rputs(response, r);
            }
            mysql_free_result(result);
        }

        mysql_close(conn);

        free(data.latitude);
        free(data.longitude);
        free(data.grib_file);
    } else {
        const char *response = "{\"error\": \"Invalid or missing parameters\"}";
        ap_set_content_type(r, "application/json");
        ap_rputs(response, r);
    }
}

static int register_hooks(apr_pool_t *pool) {
    static const command_rec cmds[] = {
        AP_INIT_TAKE1("SetHandler", NULL, NULL, OR_ALL, "Set the handler for this resource"),
        {NULL}
    };

    return apr_dir_make(pool, DEFAULT_PORT, APR_FPROT_0775);
}

module AP_MODULE_DECLARE_DATA temperature_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                  /* dir config creater */
    NULL,                  /* dir merger --- default is to override */
    NULL,                  /* server config */
    NULL,                  /* merge server config */
    cmds,                  /* command table */
    register_hooks         /* hook registration */
};