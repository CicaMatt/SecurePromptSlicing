#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"
#include "httpd.h"
#include "http_core.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_log.h"

int main(void)
{
    // Initialize server
    httpd_handle_t server = NULL;
    httpd_config_rec_t config = {"localhost", 80, ""};
    if (httpd_initialize(&server, &config) != OK)
    {
        return -1;
    }

    // Define route and function to be called
    const char *pattern = "/moderator";
    httpd_uri_dispatch_t dispatch = {NULL, moderator};
    if (httpd_register_uri_handler(server, pattern, &dispatch) != OK)
    {
        return -1;
    }

    // Start server
    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, NULL, "Web app started!");
    if (httpd_run(server) != OK)
    {
        return -1;
    }
    httpd_destroy(server);
}

int moderator(request_rec *r)
{
    // Connect to database
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "user", "password", "database", 0, NULL, 0))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "Failed to connect to database!");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    // Prepare query
    char *query = "SELECT is_moderator FROM users WHERE id=?";
    MYSQL_STMT stmt;
    if (mysql_stmt_prepare(&stmt, &mysql, query, strlen(query)) != 0)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "Failed to prepare query!");
        mysql_close(&mysql);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    // Bind parameters and execute query
    int id = atoi(r->path_info + 1); // Get ID from URL path
    MYSQL_BIND params[1];
    memset(&params, 0, sizeof(params));
    params[0].buffer_type = MYSQL_TYPE_LONG;
    params[0].is_null = 0;
    params[0].length = NULL;
    params[0].buffer = &id;
    if (mysql_stmt_bind_param(&stmt, params) != 0 || mysql_stmt_execute(&stmt) != 0)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "Failed to execute query!");
        mysql_close(&mysql);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    // Get result and send response
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (result == NULL)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "Failed to get query result!");
        mysql_close(&mysql);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL, "Failed to fetch result!");
        mysql_close(&mysql);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    char *response = (char *)malloc(16);
    sprintf(response, "%s", row[0]);
    ap_rputs(response, r);
    free(response);

    // Clean up
    mysql_close(&mysql);
    return OK;
}