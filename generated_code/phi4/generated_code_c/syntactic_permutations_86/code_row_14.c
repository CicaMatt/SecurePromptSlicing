#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void handle_request(int client_socket, const char *request);
MYSQL* init_db();
void close_db(MYSQL *conn);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024);
        handle_request(new_socket, buffer);
        close(new_socket);
    }

    return 0;
}

void handle_request(int client_socket, const char *request) {
    MYSQL *conn = init_db();
    
    // Parse the request to extract parameters
    char latitude[50], longitude[50], year[5], month[3], day[3], grib_file[100];
    sscanf(request, "GET /api/temperature_for_location?latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
           latitude, longitude, year, month, day, grib_file);

    // Construct SQL query
    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM temperature_data WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "MySQL error: %s\n", mysql_error(conn));
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);
        
        char response[256];
        snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row ? row[0] : "null");
        
        write(client_socket, response, strlen(response));
    }

    close_db(conn);
}

MYSQL* init_db() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    return conn;
}

void close_db(MYSQL *conn) {
    if (conn != NULL && mysql_ping(conn) == 0) {
        mysql_close(conn);
    }
}