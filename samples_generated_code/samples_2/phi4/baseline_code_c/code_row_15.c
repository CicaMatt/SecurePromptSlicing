#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 4096

void handle_client(int client_socket);
int connect_to_db();
MYSQL *db_connection;
char query[1024];

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        
        handle_client(new_socket);
        close(new_socket);
    }

    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("recv");
        return;
    }

    // Parse request
    char method[10], path[100];
    sscanf(buffer, "%s %s", method, path);

    if (strncmp(path, "/api/temperature_for_location", strlen("/api/temperature_for_location")) == 0) {
        char latitude[20], longitude[20], year[5], month[3], day[3], grib_file[50];
        
        sscanf(buffer, "GET /api/temperature_for_location?latitude=%[^&]&longitude=%[^&]"
                    "&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s HTTP/1.1", 
                    latitude, longitude, year, month, day, grib_file);

        snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data "
                                       "WHERE latitude = %f AND longitude = %f AND year = '%s' "
                                       "AND month = '%s' AND day = '%s' AND grib_file = '%s'",
                atof(latitude), atof(longitude), year, month, day, grib_file);

        if (connect_to_db() == 0) {
            if (mysql_query(db_connection, query)) {
                fprintf(stderr, "%s\n", mysql_error(db_connection));
            } else {
                MYSQL_RES *result = mysql_store_result(db_connection);
                if (result) {
                    MYSQL_ROW row;
                    if ((row = mysql_fetch_row(result))) {
                        char response[BUFFER_SIZE];
                        snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nMax Temperature: %s", row[0]);
                        send(client_socket, response, strlen(response), 0);
                    } else {
                        const char *no_data = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nNo data found.";
                        send(client_socket, no_data, strlen(no_data), 0);
                    }
                    mysql_free_result(result);
                }
            }
            mysql_close(db_connection);
        } else {
            const char *db_error = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nDatabase connection error.";
            send(client_socket, db_error, strlen(db_error), 0);
        }
    } else {
        const char *not_found = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nEndpoint not found.";
        send(client_socket, not_found, strlen(not_found), 0);
    }
}

int connect_to_db() {
    db_connection = mysql_init(NULL);

    if (!mysql_real_connect(db_connection, "localhost", "username", "password",
                            "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(db_connection));
        return -1;
    }
    return 0;
}