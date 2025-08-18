#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "httpd.h"
#include "http_config.h"
#include "http_protocol.h"
#include "ap_config.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "weather_data"

static int temperature_handler(request_rec *r) {
    if (strcmp(r->handler, "temperature-handler") != 0) {
        return DECLINED;
    }

    char lat[10], lon[11], year[5], month[3];

    sscanf(r->args, "latitude=%[^;];longitude=%[^;];year=%[^;];month=%s", lat, lon, year, month);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Database connection failed: %s", mysql_error(conn));
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s",
             lat, lon, year, month);

    if (mysql_query(conn, query)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "MySQL query failed: %s", mysql_error(conn));
        mysql_close(conn);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Failed to get query result: %s", mysql_error(conn));
        mysql_close(conn);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row && row[0]) {
        ap_set_content_type(r, "application/json");
        char *response = apr_psprintf(r->pool, "{\"max_temperature\": \"%s\"}", row[0]);
        ap_rwrite(response, strlen(response), r);
    } else {
        ap_set_content_type(r, "application/json");
        ap_rwrite("{\"error\":\"No data found\"}", 24, r);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return OK;
}

static void register_hooks(apr_pool_t *pool) {
    ap_hook_handler(temperature_handler, NULL, NULL, APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA temperature_module = {
    STANDARD20_MODULE_STUFF,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    register_hooks
};