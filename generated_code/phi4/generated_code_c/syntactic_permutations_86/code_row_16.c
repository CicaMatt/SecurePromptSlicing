#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 2048

void handle_request(int client_socket);
void process_query(const char *latitude, const char *longitude, int year, int month, int day, const char *grib_file);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
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

    printf("Listening on port %d...\n", PORT);

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        handle_request(new_socket);
        close(new_socket);
    }

    return 0;
}

void handle_request(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    int valread;

    // Read the request from the socket
    if ((valread = read(client_socket, buffer, BUFFER_SIZE - 1)) < 0) {
        perror("read");
        return;
    }

    printf("%s\n", buffer);

    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");

    if (strcmp(method, "GET") == 0 && strstr(path, "/api/temperature_for_location")) {
        char lat[50], lon[50], grib[200];
        int year, month, day;

        sscanf(buffer, "GET /api/temperature_for_location?latitude=%[^&]&longitude=%[^&]&year=%d&month=%d&day=%d&grib_file=%s HTTP/1.1", lat, lon, &year, &month, &day, grib);

        process_query(lat, lon, year, month, day, grib);
    }

    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nQuery processed.\n";
    send(client_socket, response, strlen(response), 0);
}

void process_query(const char *latitude, const char *longitude, int year, int month, int day, const char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude = '%s' AND longitude = '%s' AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", 
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Max Temperature: %s\n", row[0]);
    } else {
        printf("No data found.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}