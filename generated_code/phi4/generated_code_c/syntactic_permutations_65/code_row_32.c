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

int main(int argc, char *argv[]) {
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[256];
    FILE *file;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    // Bind the socket
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR on binding");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        bzero(buffer, 256);
        int n = read(newsockfd, buffer, 255);
        if (n < 0) 
            error("ERROR reading from socket");

        printf("Received: %s\n", buffer);

        // Extract file name and content length
        char *filename = strtok(buffer, ",");
        long content_length = atol(strtok(NULL, ","));
        char *file_content = strtok(NULL, ",");

        if (filename && content_length > 0) {
            // Remove leading space from file content
            while (*file_content == ' ') {
                file_content++;
            }

            // Save the file
            file = fopen(filename, "wb");
            if (!file) {
                error("ERROR opening file");
            }
            fwrite(file_content, 1, content_length, file);
            fclose(file);

            printf("File %s saved successfully.\n", filename);
        }

        close(newsockfd);
    }

    close(sockfd);
    return 0;
}


To use this C code as a server:
- Compile the program using `gcc -o server server.c`.
- Run it with `./server`.

For the client-side (HTML form), you can create an HTML file like this:


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Upload PDF</title>
</head>
<body>
    <form id="uploadForm" enctype="multipart/form-data">
        <input type="file" name="pdfFile" accept=".pdf" required>
        <button type="submit">Upload</button>
    </form>

    <script>
        document.getElementById('uploadForm').addEventListener('submit', function(event) {
            event.preventDefault();

            const formData = new FormData();
            const fileInput = document.querySelector('input[name="pdfFile"]');
            const file = fileInput.files[0];

            if (file.type !== "application/pdf") {
                alert("Please upload a PDF file.");
                return;
            }

            formData.append('pdfFile', file);

            fetch(`http://localhost:8080`, {
                method: 'POST',
                body: JSON.stringify({
                    filename: file.name,
                    contentLength: file.size,
                    content: Array.from(new Uint8Array(file).buffer)
                })
            }).then(response => response.text())
              .then(data => console.log(data))
              .catch(error => console.error('Error:', error));
        });
    </script>
</body>
</html>


Note: This HTML form uses JavaScript to send a POST request with the file data. You might need additional server-side logic to handle this request correctly, as the C code provided is a basic TCP server example.