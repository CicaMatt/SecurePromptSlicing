#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "uv.h"

#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "db"
#define MYSQL_HOST "localhost"
#define PORT 8080

typedef struct {
    uv_tcp_t* client;
    char buffer[1024];
    size_t len;
} request_data;

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        return;
    }

    uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(server->loop, client);
    if (uv_accept(server, (uv_stream_t*)client) == 0) {
        uv_read_start((uv_stream_t*)client, uv_alloc_buffer, on_read);
    } else {
        free(client);
    }
}

void on_read(uv_stream_t *stream, ssize_t nread, const uv_buf_t* buf) {
    request_data* data = (request_data*) stream->data;
    if (nread < 0 && nread != UV_EOF) {
        fprintf(stderr, "Read error %s\n", uv_strerror(nread));
        uv_close((uv_handle_t*)stream, free);
        return;
    }

    if (nread == 0 || nread == UV.EOF) return;

    data->len += nread;
    memmove(data->buffer, buf->base, data->len);

    char* request = strstr(data->buffer, "/api/temperature_for_location?");
    if (request) {
        MYSQL *conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
            fprintf(stderr, "MySQL connection failed: %s\n", mysql_error(conn));
            goto end;
        }

        char* lat_str = strstr(request, "lat=");
        char* lon_str = strstr(request, "lon=");
        char* year_str = strstr(request, "year=");
        char* month_str = strstr(request, "month=");

        if (lat_str && lon_str && year_str && month_str) {
            float lat, lon;
            int year, month;

            sscanf(lat_str + 4, "%f", &lat);
            sscanf(lon_str + 4, "&year=%d", &year);
            sscanf(year_str + 5, "&month=%d", &month);

            char query[256];
            snprintf(query, sizeof(query),
                     "SELECT MAX(temperature) FROM temperatures WHERE latitude = %f AND longitude = %f AND year = %d AND month = %d",
                     lat, lon, year, month);

            if (mysql_query(conn, query)) {
                fprintf(stderr, "MySQL query failed: %s\n", mysql_error(conn));
                goto end;
            }

            MYSQL_RES *result = mysql_store_result(conn);
            if (result && mysql_num_rows(result) > 0) {
                MYSQL_ROW row = mysql_fetch_row(result);
                char response[128];
                snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"max_temperature\": %s}", row[0]);
                uv_write_t* req = (uv_write_t*) malloc(sizeof(uv_write_t));
                uv_buf_t buffer = uv_buf_init(response, strlen(response));
                uv_write(req, stream, &buffer, 1, NULL);
            } else {
                char response[] = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"max_temperature\": null}";
                uv_write_t* req = (uv_write_t*) malloc(sizeof(uv_write_t));
                uv_buf_t buffer = uv_buf_init(response, strlen(response));
                uv_write(req, stream, &buffer, 1, NULL);
            }
        }

end:
        mysql_close(conn);
    }

    free(data->buffer);
    free(data);
    uv_close((uv_handle_t*)stream, free);
}

int main() {
    uv_loop_t *loop = uv_default_loop();
    uv_tcp_t server;
    struct sockaddr_in addr;

    uv_tcp_init(loop, &server);

    uv_ip4_addr("0.0.0.0", PORT, &addr);
    uv_listen((uv_stream_t*) &server, 128, on_new_connection);

    printf("Server listening on port %d\n", PORT);
    return uv_run(loop, UV_RUN_DEFAULT);
}