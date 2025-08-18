#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#include <mysql/mysql.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket, MYSQL *conn);

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return 1;
    }
#endif

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "Database connection error: %s\n", mysql_error(conn));
        return 1;
    }

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("Accept failed");
            continue;
        }

        handle_client(client_socket, conn);

        close(client_socket);
    }

#ifdef _WIN32
    WSACleanup();
#endif

    mysql_close(conn);
    return 0;
}

void handle_client(int client_socket, MYSQL *conn) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received < 0) {
        perror("Receive failed");
        return;
    }

    char *user_id_start = strstr(buffer, "GET /check_moderator?user_id=");
    if (!user_id_start) {
        const char *response = "Invalid request";
        send(client_socket, response, strlen(response), 0);
        return;
    }
    
    user_id_start += 27; // length of the GET /check_moderator?user_id=
    char *user_id_end = strchr(user_id_start, ' ');
    if (!user_id_end) {
        const char *response = "Invalid request";
        send(client_socket, response, strlen(response), 0);
        return;
    }

    *user_id_end = '\0';
    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE user_id='%s'", user_id_start);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        const char *response = "Internal server error";
        send(client_socket, response, strlen(response), 0);
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "Store result failed: %s\n", mysql_error(conn));
        const char *response = "Internal server error";
        send(client_socket, response, strlen(response), 0);
        return;
    }
    
    MYSQL_ROW row = mysql_fetch_row(result);
    const char *response;

    if (row && row[0] && strcmp(row[0], "1") == 0) {
        response = "User is a moderator";
    } else {
        response = "User is not a moderator";
    }

    send(client_socket, response, strlen(response), 0);
    mysql_free_result(result);
}