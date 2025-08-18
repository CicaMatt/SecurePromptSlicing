#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>

#define PORT 8080
#define BACKLOG 5
#define BUFFER_SIZE 1024

typedef struct {
    double latitude;
    double longitude;
    int year;
    int month;
    int day;
    char grib_file[256];
} RequestParams;

void parse_request(const char *request, RequestParams *params) {
    sscanf(request, "GET /api/temperature_for_location?latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%s", 
           &params->latitude, &params->longitude, &params->year, &params->month, &params->day, params->grib_file);
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        RequestParams params;
        parse_request(buffer, &params);

        MYSQL *conn = mysql_init(NULL);
        mysql_real_connect(conn, "localhost", "user", "password", "weather_db", 3306, NULL, 0);
        
        char query[BUFFER_SIZE];
        snprintf(query, sizeof(query), 
                 "SELECT MAX(temperature) FROM temperature_data WHERE latitude=%lf AND longitude=%lf AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
                 params.latitude, params.longitude, params.year, params.month, params.day, params.grib_file);
        
        mysql_query(conn, query);
        MYSQL_RES *result = mysql_store_result(conn);
        double max_temp = 0.0;
        if (mysql_num_rows(result) > 0) {
            MYSQL_ROW row = mysql_fetch_row(result);
            max_temp = atof(row[0]);
        }

        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response), 
                 "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"max_temperature\": %.2f}", max_temp);
        
        send(client_socket, response, strlen(response), 0);

        mysql_free_result(result);
        mysql_close(conn);
    }
    close(client_socket);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        handle_request(client_fd);
    }

    return 0;
}