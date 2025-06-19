#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <sys/wait.h>
    #include <signal.h>
    #include <fcntl.h>
    #include "http_server.h"
    
    struct mime_type {
        char extension[15];
        char mime_type[32];
    };
    
    struct mime_type extensions[] = {{".html", "text/html"},
                                     {".css",  "text/css"},
                                     {".js",   "application/javascript"}};
    
    void error_handling(char *message);
    char* find_mime_type(char *extension);
    int file_size(int fd);
    void add_response_header(int client_fd, char *filename, int fd);
    
    int main() {
        // 클라이언트의 요청을 받는데 사용하는 소켓 개수
        const int LISTEN_QUEUE = 8;
    
        // listen()에서 대기할 큐의 길이를 지정한다.
        if (listen(server_sock, LISTEN_QUEUE) == -1)
            error_handling("listen() error");
    
        printf("Server listen port : %d \n", PORT);
    
        int client_addr_size;
        struct sockaddr_in client_addr; // 클라이언트의 주소 정보를 담는다.
    
        // 요청을 받은 것이 있는지 확인하는데,
        // accept()로부터 연결이 수락되면 얻어진 소켓을
        // 사용해서 요청에 대한 처리를 수행하고,
        // 다시 accept()로 돌아가 다음 연결 요청을 기다린다.
        while (1) {
            client_addr_size = sizeof(struct sockaddr_in);
    
            int client_sock = accept(server_sock, (struct sockaddr *)&client_addr,
                                     &client_addr_size);
    
            if (client_sock == -1)
                error_handling("accept() error");
    
            char header[BUFSIZ];
            char method[BUFSIZ], uri[BUFSIZ], version[BUFSIZ];
    
            // 헤더정보를 읽어들인다.
            recv(client_sock, header, BUFSIZ, 0);
    
            sscanf(header, "%s %s %s", method, uri, version); // 요청메소드를 구함
    
            printf("Requested Method : %s\n", method);
            printf("Requested URI : %s\n", uri);
            printf("Requested Version : %s\n", version);
    
            if (strcmp(method, "GET") == 0) {
                // GET방식으로 요청한 경우
                if (strcmp(uri, "/hello") == 0) {
                    char query[BUFSIZ];
    
                    // 쿼리스트링을 가져온다.
                    sscanf(header, "%*s %*s %*s%[^$^\n]", query);
    
                    char *name = strtok(query, "=&");
    
                    name = strtok(NULL, "=&");
    
                    if (send_file(client_sock, "hello.html") == -1)
                        return 0;
    
                } else {
                    // 정적인 파일을 보낸다.
                    send_static_file(client_sock, uri);
                }
            } else {
                printf("Don't support %s method\n", method);
            }
        }
    
        // close()로 소켓을 닫아준다.
        close(server_sock);
    
        return 0;
    }