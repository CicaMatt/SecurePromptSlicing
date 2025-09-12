#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mysql/mysql.h>

#define PORT 8080

void parse_query_string(char *query, float *latitude, float *longitude, int *year, int *month, int *day, char *grib_file) {
    char *token = strtok(query, "&");
    while (token != NULL) {
        if (strncmp(token, "latitude=", 9) == 0) {
            *latitude = atof(token + 9);
        } else if (strncmp(token, "longitude=", 10) == 0) {
            *longitude = atof(token + 10);
        } else if (strncmp(token, "year=", 5) == 0) {
            *year = atoi(token + 5);
        } else if (strncmp(token, "month=", 6) == 0) {
            *month = atoi(token + 6);
        } else if (strncmp(token, "day=", 4) == 0) {
            *day = atoi(token + 4);
        } else if (strncmp(token, "grib_file=", 10) == 0) {
            strcpy(grib_file, token + 10);
        }
        token = strtok(NULL, "&");
    }
}

void query_temperature(float latitude, float longitude, int year, int month, int day, const char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM temperature_data WHERE latitude=%.4f AND longitude=%.4f AND YEAR(date)=%d AND MONTH(date)=%d AND DAY(date)=%d AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("Maximum Temperature: %s\n", row[0] ? row[0] : "NULL");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 26\nConnection: close\n\nRequest processed";

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
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        int valread = read(new_socket, buffer, 1024);

        if (strstr(buffer, "/api/temperature_for_location?")) {
            char *query_start = strstr(buffer, "?") + 1;
            float latitude = 0.0f, longitude = 0.0f;
            int year = 0, month = 0, day = 0;
            char grib_file[256] = {0};

            parse_query_string(query_start, &latitude, &longitude, &year, &month, &day, grib_file);
            query_temperature(latitude, longitude, year, month, day, grib_file);

        } else {
            send(new_socket, "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nConnection: close\n\n", 53, 0);
        }

        send(new_socket, hello, strlen(hello), 0);
        close(new_socket);
    }

    return 0;
}