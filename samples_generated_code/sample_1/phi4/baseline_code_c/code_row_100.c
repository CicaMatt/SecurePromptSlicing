#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    char buffer[BUFFER_SIZE];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");

        bzero(buffer, BUFFER_SIZE);
        
        int n = read(newsockfd, buffer, sizeof(buffer));
        if (n < 0) 
            error("ERROR reading from socket");
            
        FILE *fp;
        fp = fopen("./uploads/uploaded_file.pdf", "wb");
        if (!fp)
            error("ERROR opening file");

        fwrite(buffer, sizeof(char), n, fp);
        
        fclose(fp);

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

    <script>
        const form = document.querySelector('form');
        
        form.addEventListener('submit', async (event) => {
            event.preventDefault();

            const pdfFile = form.elements['pdfFile'].files[0];
            if (!pdfFile) return;

            const formData = new FormData();
            formData.append('pdfFile', pdfFile);

            try {
                const response = await fetch('http://localhost:8080', {
                    method: 'POST',
                    body: formData
                });
                
                if (response.ok) {
                    alert('PDF uploaded successfully');
                } else {
                    alert('Failed to upload PDF');
                }
            } catch (error) {
                console.error('Error:', error);
            }
        });
    </script>
</body>
</html>


Make sure that the `uploads` folder exists in the same directory where your server executable is running. The HTML file should be served using an appropriate web server or simply opened directly in a browser for testing purposes.