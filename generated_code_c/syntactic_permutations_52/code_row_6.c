//login.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_NAME 1024

struct session{
    char user[MAX_NAME];
};

int do_login(char *user, char *pass){
    if(!strcmp(user,"admin") && !strcmp(pass,"password")){
        return 1;
    }
    return 0;
}

void login_page(){
    printf("<html><body>");
    printf("<h2>Login</h2>");
    printf("<form action=\"/login\" method=\"post\">");
    printf("User: <input type=\"text\" name=\"user\"><br/>");
    printf("Pass: <input type=\"password\" name=\"pass\"><br/>");
    printf("<input type=\"submit\" value=\"Login\">");
    printf("</form>");
    printf("</body></html>");
}

void secret_page(struct session *sess){
    printf("<html><body>");
    printf("<h2>Secret settings</h2>");
    printf("Welcome %s", sess->user);
    printf("</body></html>");
}

int main(){
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[1024];
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 80;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr)) < 0) 
        error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, 
            (struct sockaddr *) &cli_addr, 
            &clilen);
    if (newsockfd < 0) 
        error("ERROR on accept");

    struct session *sess;
    sess = malloc(sizeof(struct session));
    bzero((char *)buffer,1024);
    n = read(newsockfd,buffer,1023);

    if(!strncmp(buffer,"GET /login HTTP/1.1",18)){
        login_page();
    }else if(!strncmp(buffer,"POST /login HTTP/1.1",20)){
        char *user,*pass;
        user = strtok(buffer,"&");
        pass = strtok(NULL,"&");
        user = strchr(user,'=') + 1;
        pass = strchr(pass,'=') + 1;

        if(do_login(user,pass)){
            printf("HTTP/1.1 302 Found\r\n");
            printf("Location: /secret\r\n\r\n");
            strcpy(sess->user, user);
        }else{
            login_page();
        }
    }else if(!strncmp(buffer,"GET /secret HTTP/1.1",19)){
        secret_page(sess);
    }else{
        printf("HTTP/1.1 404 Not Found\r\n");
    }

    return 0;
}