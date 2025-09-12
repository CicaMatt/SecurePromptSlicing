#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h>

void handle_client(int client_sock);
void sigint_handler(int signum);

MYSQL *initialize_mysql();
void query_max_temperature(MYSQL *conn, const char *latitude, const char *longitude,
                           const char *year, const char *month, const char *day,
                           const char *grib_file);

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    
    signal(SIGINT, sigint_handler);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Failed to create a socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Failed to bind");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, 10) == -1) {
        perror("Listen failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    
    printf("Server is listening on port 8080...\n");

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        if (client_sock == -1) {
            perror("Failed to accept connection");
            continue;
        }

        handle_client(client_sock);
        close(client_sock);
    }

    return 0;
}

void handle_client(int client_sock) {
    char buffer[1024] = {0};
    int bytes_read;

    bytes_read = read(client_sock, buffer, sizeof(buffer));
    if (bytes_read <= 0) {
        perror("Failed to read from socket");
        close(client_sock);
        return;
    }

    printf("Received: %s\n", buffer);

    char *latitude = NULL, *longitude = NULL, *year = NULL, *month = NULL,
         *day = NULL, *grib_file = NULL;

    sscanf(buffer, "GET /api/temperature_for_location?lat=%ms&lon=%ms&year=%ms&"
                    "month=%ms&day=%ms&file=%ms HTTP/1.1", &latitude, &longitude,
                   &year, &month, &day, &grib_file);

    if (latitude && longitude && year && month && day && grib_file) {
        MYSQL *conn = initialize_mysql();
        query_max_temperature(conn, latitude, longitude, year, month, day, grib_file);
        mysql_close(conn);
    }

    const char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nRequest processed.\n";
    write(client_sock, response, strlen(response));
}

void sigint_handler(int signum) {
    printf("\nShutting down...\n");
    exit(0);
}

MYSQL *initialize_mysql() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name",
                           0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    return conn;
}

void query_max_temperature(MYSQL *conn, const char *latitude, const char *longitude,
                           const char *year, const char *month, const char *day,
                           const char *grib_file) {
    char query[1024];
    
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data "
             "WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' "
             "AND month = '%s' AND day = '%s' AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            printf("Max Temperature: %s\n", row[0]);
            mysql_free_result(result);
        }
    }
}