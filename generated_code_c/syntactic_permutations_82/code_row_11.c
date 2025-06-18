#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

#define BUFFERSIZE 1024
#define NUM_ARGS 3

int main(void)
{
    // Create a web app
    int sockfd;
    char buffer[BUFFERSIZE];
    char *message = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: close\r\n\r\n<!DOCTYPE html><html lang=\"en\"><head><title>Web App</title></head><body>Welcome to the web app!</body></html>\r\n";
    char *error_message = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: close\r\n\r\n<!DOCTYPE html><html lang=\"en\"><head><title>Error</title></head><body>An error occurred.</body></html>\r\n";
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_addr_size = sizeof(cli_addr);

    // Create a socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket() failed");
        exit(1);
    }

    // Set up the server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("bind() failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(sockfd, 3) < 0)
    {
        perror("listen() failed");
        exit(1);
    }

    while (1)
    {
        int connfd;

        // Accept an incoming connection
        connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_addr_size);
        if (connfd < 0)
        {
            perror("accept() failed");
            continue;
        }

        // Handle the connection
        handle_connection(connfd);

        // Close the socket
        close(connfd);
    }

    return 0;
}

void handle_connection(int connfd)
{
    char buffer[BUFFERSIZE];
    char *method = NULL;
    char *path = NULL;
    char *version = NULL;
    int is_static = 0;
    char *file_type = NULL;
    struct stat file_info;
    int file_fd;

    // Receive data from the client
    recv(connfd, buffer, BUFFERSIZE, 0);

    // Parse the request line
    method = strtok(buffer, " \t\r\n");
    path = strtok(NULL, " \t");
    version = strtok(NULL, " \t\r\n");
    if (method == NULL || path == NULL || version == NULL)
    {
        send_error(connfd);
        return;
    }

    // Check the method
    if (strcasecmp(method, "GET") != 0)
    {
        send_error(connfd);
        return;
    }

    // Check the path
    if (strncmp(path, "/api", 4) == 0)
    {
        char *query = NULL;
        query = strtok(NULL, " \t");
        if (query == NULL)
        {
            send_error(connfd);
            return;
        }

        // Get the payload parameter from the URL
        char *payload = NULL;
        payload = strtok(query, "&=");
        if (payload == NULL)
        {
            send_error(connfd);
            return;
        }

        // Load the payload into a dictionary
        char *key = NULL;
        char *value = NULL;
        key = strtok(NULL, "&=");
        if (key == NULL)
        {
            send_error(connfd);
            return;
        }
        value = strtok(NULL, "&=");
        if (value == NULL)
        {
            send_error(connfd);
            return;
        }

        // Return the name value from the dictionary
        char *name = value;
        send_response(connfd, name);
    }
    else
    {
        is_static = 1;
        int cgi = 0;
        char *file_path = NULL;

        // Check the file type
        if (strchr(path, '.') == NULL)
        {
            send_error(connfd);
            return;
        }

        // Determine the file path
        file_path = path + 1;
        if (*file_path != '\0' && *file_path == '/')
        {
            send_error(connfd);
            return;
        }

        // Check for CGI
        cgi = !!strchr(file_path, '?');
        if (cgi)
        {
            *strchr(file_path, '?') = '\0';
        }

        // Open the file
        if (stat(file_path, &file_info) < 0)
        {
            send_error(connfd);
            return;
        }

        if (!cgi && S_ISDIR(file_info.st_mode))
        {
            strcpy(file_path, "index.html");
        }

        // Check the file type
        file_type = get_file_type(file_path);
        if (file_type == NULL)
        {
            send_error(connfd);
            return;
        }

        // Open the file
        file_fd = open(file_path, O_RDONLY);
        if (file_fd < 0)
        {
            send_error(connfd);
            return;
        }

        // Send the response
        char content_length[32];
        sprintf(content_length, "%d", (int)file_info.st_size);
        if (is_static)
        {
            send_response(connfd, file_path, content_length, "text/html");
        }
        else
        {
            send_response(connfd, name);
        }
    }
}

char *get_file_type(char *file_path)
{
    if (strstr(file_path, ".html"))
    {
        return "text/html";
    }
    else if (strstr(file_path, ".css"))
    {
        return "text/css";
    }
    else if (strstr(file_path, ".js"))
    {
        return "application/javascript";
    }
    else if (strstr(file_path, ".png"))
    {
        return "image/png";
    }
    else if (strstr(file_path, ".jpg"))
    {
        return "image/jpeg";
    }
    else if (strstr(file_path, ".ico"))
    {
        return "image/x-icon";
    }
    else
    {
        return NULL;
    }
}

void send_error(int connfd)
{
    char buffer[BUFFERSIZE];
    sprintf(buffer, "%s", error_message);
    send(connfd, buffer, strlen(buffer), 0);
}

void send_response(int connfd, char *file_path, char *content_length, char *content_type)
{
    char buffer[BUFFERSIZE];
    sprintf(buffer, "HTTP/1.1 200 OK\r\nContent-Type: %s; charset=UTF-8\r\nConnection: close\r\n", content_type);
    send(connfd, buffer, strlen(buffer), 0);

    sprintf(buffer, "Content-Length: %d\r\n\r\n", (int)content_length);
    send(connfd, buffer, strlen(buffer), 0);

    char *file_data = NULL;
    file_data = malloc(sizeof(char) * content_length);
    if (file_data == NULL)
    {
        perror("malloc() failed");
        exit(1);
    }

    int read_bytes = read(file_fd, file_data, content_length);
    if (read_bytes < 0)
    {
        perror("read() failed");
        exit(1);
    }

    send(connfd, file_data, content_length, 0);
}

void send_response(int connfd, char *name)
{
    char buffer[BUFFERSIZE];
    sprintf(buffer, "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: close\r\n\r\n");
    send(connfd, buffer, strlen(buffer), 0);

    sprintf(buffer, "<!DOCTYPE html><html lang=\"en\"><head><title>Web App</title></head><body>Welcome to the web app!<br />Your name is %s.</body></html>\r\n", name);
    send(connfd, buffer, strlen(buffer), 0);
}