#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <httpd.h>
#include <http_config.h>
#include <http_protocol.h>

static int handle_temperature_request(request_rec *r) {
    if (strcmp(r->handler, "temperature_handler") != 0)
        return DECLINED;

    char latitude[32], longitude[32], year[8], month[3], day[3], grib_file[256];
    
    // Extract query parameters
    const char *lat = apr_table_get(r->args, "latitude");
    const char *lon = apr_table_get(r->args, "longitude");
    const char *yr = apr_table_get(r->args, "year");
    const char *mnth = apr_table_get(r->args, "month");
    const char *dy = apr_table_get(r->args, "day");
    const char *grib = apr_table_get(r->args, "grib_file");

    if (!lat || !lon || !yr || !mnth || !dy || !grib) {
        r->content_type = "text/plain";
        ap_rputs("Missing parameters", r);
        return HTTP_BAD_REQUEST;
    }

    strncpy(latitude, lat, sizeof(latitude));
    strncpy(longitude, lon, sizeof(longitude));
    strncpy(year, yr, sizeof(year));
    strncpy(month, mnth, sizeof(month));
    strncpy(day, dy, sizeof(day));
    strncpy(grib_file, grib, sizeof(grib_file));

    // Connect to MySQL database
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        r->content_type = "text/plain";
        ap_rprintf(r, "Database connection failed: %s\n", mysql_error(conn));
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    // Prepare the SQL query
    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperatures "
             "WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
             mysql_real_escape_string(conn, latitude),
             mysql_real_escape_string(conn, longitude),
             mysql_real_escape_string(conn, year),
             mysql_real_escape_string(conn, month),
             mysql_real_escape_string(conn, day),
             mysql_real_escape_string(conn, grib_file));

    // Execute the query
    if (mysql_query(conn, query)) {
        r->content_type = "text/plain";
        ap_rprintf(r, "Query failed: %s\n", mysql_error(conn));
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        r->content_type = "text/plain";
        ap_rprintf(r, "Failed to retrieve result: %s\n", mysql_error(conn));
        mysql_close(conn);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    // Fetch the result
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row && row[0]) {
        r->content_type = "text/plain";
        ap_rprintf(r, "Max Temperature: %s\n", row[0]);
    } else {
        r->content_type = "text/plain";
        ap_rputs("No temperature data found for the specified parameters.", r);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return OK;
}

static void register_hooks(apr_pool_t *pool) {
    ap_hook_handler(handle_temperature_request, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA temperature_module = {
    STANDARD20_MODULE_STUFF,
    NULL,                  /* create per-dir config structures */
    NULL,                  /* merge  per-dir config structures */
    NULL,                  /* create per-server config structures */
    NULL,                  /* merge  per-server config structures */
    NULL,                  /* table of config file commands       */
    register_hooks         /* register hooks                      */
};