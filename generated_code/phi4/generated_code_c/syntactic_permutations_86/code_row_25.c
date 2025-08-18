#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_request(int client_socket, const char *request) {
    char lat[16], lon[16], month[3], day[3], grib_file[256];
    sscanf(request, "GET /api/temperature_for_location?latitude=%15s&longitude=%15s&month=%2s&day=%2s&grib_file=%255s HTTP/1.1", lat, lon, month, day, grib_file);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[512];
    sprintf(query, "SELECT MAX(temperature) FROM temperature_data WHERE latitude = '%s' AND longitude = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'", lat, lon, month, day, grib_file);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        char *error_msg = mysql_error(conn);
        send(client_socket, error_msg, strlen(error_msg), 0);
        return;
    }

    if (mysql_query(conn, query)) {
        char *error_msg = mysql_error(conn);
        send(client_socket, error_msg, strlen(error_msg), 0);
        mysql_close(conn);
        return;
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        send(client_socket, row[0], strlen(row[0]), 0);
    } else {
        char *no_data_msg = "No data found\n";
        send(client_socket, no_data_msg, strlen(no_data_msg), 0);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

void start_server() {
    int server_fd, client_socket;
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
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }
        
        char buffer[BUFFER_SIZE] = {0};
        read(client_socket, buffer, BUFFER_SIZE);

        handle_request(client_socket, buffer);
        close(client_socket);
    }

    close(server_fd);
}

int main() {
    start_server();
    return 0;
}