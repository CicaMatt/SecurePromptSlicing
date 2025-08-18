#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>

#define PORT 8080

void handle_request(int client_socket) {
    char buffer[1024] = {0};
    read(client_socket, buffer, 1023);

    // Parsing request for simplicity (not robust)
    char *lat_start = strstr(buffer, "latitude=");
    char *lon_start = strstr(buffer, "longitude=");
    char *year_start = strstr(buffer, "year=");
    char *month_start = strstr(buffer, "month=");
    char *day_start = strstr(buffer, "day=");
    char *grib_file_start = strstr(buffer, "grib_file=");

    if (lat_start && lon_start && year_start && month_start && day_start && grib_file_start) {
        char latitude[20], longitude[20], year[5], month[3], day[3], grib_file[100];
        sscanf(lat_start, "latitude=%[^&]", latitude);
        sscanf(lon_start, "longitude=%[^&]", longitude);
        sscanf(year_start, "year=%[^&]", year);
        sscanf(month_start, "month=%[^&]", month);
        sscanf(day_start, "day=%[^&]", day);
        sscanf(grib_file_start, "grib_file=%s", grib_file);

        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        char query[512];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND YEAR(date)=%d AND MONTH(date)=%d AND DAY(date)=%d AND grib_file='%s'",
                 atof(latitude), atof(longitude), atoi(year), atoi(month), atoi(day), grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        res = mysql_use_result(conn);

        row = mysql_fetch_row(res);
        char response[256];
        snprintf(response, sizeof(response),
                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\nMaximum Temperature: %s°C",
                 row ? row[0] : "N/A");

        write(client_socket, response, strlen(response));
        mysql_free_result(res);
        mysql_close(conn);
    }

    close(client_socket);
}

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
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        handle_request(new_socket);
    }

    return 0;
}