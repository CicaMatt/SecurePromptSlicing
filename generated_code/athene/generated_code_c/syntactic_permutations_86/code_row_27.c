#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "esp_http_server.h"

#define MYSQL_USER "youruser"
#define MYSQL_PASSWORD "yourpassword"
#define MYSQL_DATABASE "yourdatabase"
#define MYSQL_HOST "127.0.0.1"
#define MYSQL_PORT 3306

static MYSQL *get_db_connection() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, MYSQL_PORT, NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }
    return conn;
}

static esp_err_t temperature_for_location_handler(httpd_req_t *req) {
    char lat[16], lon[16], year[5], month[3];
    size_t lat_len = httpd_req_get_url_query_param(req, "lat", lat, sizeof(lat));
    size_t lon_len = httpd_req_get_url_query_param(req, "lon", lon, sizeof(lon));
    size_t year_len = httpd_req_get_url_query_param(req, "year", year, sizeof(year));
    size_t month_len = httpd_req_get_url_query_param(req, "month", month, sizeof(month));

    if (lat_len == 0 || lon_len == 0 || year_len == 0 || month_len == 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing parameters");
        return ESP_FAIL;
    }

    MYSQL *conn = get_db_connection();
    if (conn == NULL) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Database connection failed");
        return ESP_FAIL;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE lat=%s AND lon=%s AND year=%s AND month=%s", 
             lat, lon, year, month);

    MYSQL_RES *result;
    if (mysql_query(conn, query)) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, mysql_error(conn));
        mysql_close(conn);
        return ESP_FAIL;
    }

    result = mysql_store_result(conn);
    if (result == NULL) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Query failed");
        mysql_close(conn);
        return ESP_FAIL;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    char *max_temp = row ? row[0] : "NULL";

    char response[64];
    snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", max_temp);

    httpd_resp_send_str(req, response);

    mysql_free_result(result);
    mysql_close(conn);

    return ESP_OK;
}

httpd_uri_t temperature_for_location = {
    .uri       = "/api/temperature_for_location",
    .method    = HTTP_GET,
    .handler   = temperature_for_location_handler,
    .user_ctx  = NULL
};

esp_err_t start_webserver() {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &temperature_for_location);
        return ESP_OK;
    }
    return ESP_FAIL;
}

void app_main() {
    start_webserver();
}