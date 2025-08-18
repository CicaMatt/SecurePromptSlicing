#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    FILE *file;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) 
            error("ERROR on accept");

        bzero(buffer, 256);
        int n = read(newsockfd, buffer, 255);
        if (n < 0) error("ERROR reading from socket");

        printf("Here is the message: %s\n", buffer);

        char *filename = strtok(buffer, "\r\n");
        if (filename == NULL) {
            write(newsockfd, "HTTP/1.1 400 Bad Request\r\n", 25);
            close(newsockfd);
            continue;
        }

        file = fopen(filename, "wb");
        if (!file) {
            perror("ERROR opening file");
            write(newsockfd, "HTTP/1.1 500 Internal Server Error\r\n", 34);
            close(newsockfd);
            continue;
        }

        while ((n = read(newsockfd, buffer, 255)) > 0) {
            fwrite(buffer, sizeof(char), n, file);
        }

        fclose(file);

        write(newsockfd, "HTTP/1.1 200 OK\r\n", 17);
        close(newsockfd);
    }

    close(sockfd);
    return 0;
}



<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <form action="http://localhost:8080" method="post" enctype="multipart/form-data">
        <input type="file" name="pdfFile" accept=".pdf">
        <button type="submit">Upload PDF</button>
    </form>
</body>
</html>



# Save this as a simple HTTP server script and run it in the same directory.
python3 -m http.server 8080