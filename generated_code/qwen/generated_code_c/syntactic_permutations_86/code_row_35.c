#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>

#define PORT 8080

void query_temperature(MYSQL *conn, double latitude, double longitude, int year, int month, int day, const char* grib_file) {
    char query[256];
    snprintf(query, sizeof(query), 
        "SELECT MAX(temperature) FROM weather_data WHERE latitude = %f AND longitude = %f AND YEAR(date) = %d AND MONTH(date) = %d AND DAY(date) = %d AND grib_file = '%s'", 
        latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL && row[0] != NULL)
        printf("Maximum Temperature: %s\n", row[0]);
    else
        printf("No data found.\n");

    mysql_free_result(result);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\n";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
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

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))) {
        read(new_socket, buffer, 1024);
        printf("%s\n", buffer);

        if (strstr(buffer, "/api/temperature_for_location") != NULL) {
            send(new_socket, hello, strlen(hello), 0);

            double latitude, longitude;
            int year, month, day;
            char grib_file[256];

            // Example parsing, should be done more robustly in production
            sscanf(buffer, "GET /api/temperature_for_location?latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%255s", 
                   &latitude, &longitude, &year, &month, &day, grib_file);

            MYSQL *conn = mysql_init(NULL);
            if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(EXIT_FAILURE);
            }

            query_temperature(conn, latitude, longitude, year, month, day, grib_file);

            mysql_close(conn);
        } else {
            send(new_socket, "HTTP/1.1 404 Not Found\nContent-Type: text/plain\n\n", 39, 0);
        }

        close(new_socket);
    }

    return 0;
}