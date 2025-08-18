#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <mysql/mysql.h>

#define PORT 8080

void handle_request(int client_socket);
char* extract_param(const char *buffer, const char *param_name);
void send_response(int client_socket, int status_code, const char *body);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    int valread = read(client_socket, buffer, sizeof(buffer));
    
    if (valread > 0 && strstr(buffer, "GET /api/temperature_for_location")) {
        char *latitude = extract_param(buffer, "latitude=");
        char *longitude = extract_param(buffer, "longitude=");
        char *year = extract_param(buffer, "year=");
        char *month = extract_param(buffer, "month=");
        char *day = extract_param(buffer, "day=");
        char *grib_file = extract_param(buffer, "grib_file=");

        if (latitude && longitude && year && month && day && grib_file) {
            MYSQL *conn;
            conn = mysql_init(NULL);
            
            if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
                send_response(client_socket, 500, "Internal Server Error");
                mysql_close(conn);
                return;
            }

            char query[1024];
            snprintf(query, sizeof(query), 
                     "SELECT MAX(temperature) FROM temperature_data WHERE "
                     "latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'", 
                     latitude, longitude, year, month, day, grib_file);

            if (mysql_query(conn, query)) {
                send_response(client_socket, 500, "Internal Server Error");
            } else {
                MYSQL_RES *result = mysql_store_result(conn);
                MYSQL_ROW row;

                if ((row = mysql_fetch_row(result))) {
                    char response[128];
                    snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
                    send_response(client_socket, 200, response);
                } else {
                    send_response(client_socket, 404, "Not Found");
                }

                mysql_free_result(result);
            }
            mysql_close(conn);
        } else {
            send_response(client_socket, 400, "Bad Request");
        }
    } else {
        send_response(client_socket, 404, "Not Found");
    }
}

char* extract_param(const char *buffer, const char *param_name) {
    const char *start = strstr(buffer, param_name);
    if (!start) return NULL;

    start += strlen(param_name);
    char *end = strchr(start, '&');
    
    size_t length = end ? (size_t)(end - start) : strlen(start);
    char *result = malloc(length + 1);
    strncpy(result, start, length);
    result[length] = '\0';
    
    return result;
}

void send_response(int client_socket, int status_code, const char *body) {
    char header[256];
    snprintf(header, sizeof(header), 
             "HTTP/1.1 %d OK\r\nContent-Type: application/json\r\nContent-Length: %zu\r\nConnection: close\r\n\r\n%s", 
             status_code, strlen(body), body);
    
    send(client_socket, header, strlen(header), 0);
}