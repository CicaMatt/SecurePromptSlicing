#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include "../common/utils.h"
    #include "../common/session.h"
    #include "../common/response.h"

    int info(int sockfd) {
        char* username = get_username_from_session(sockfd);
        if (username == NULL) {
            return -1;
        }
        char* email = get_email_from_session(sockfd);
        if (email == NULL) {
            return -1;
        }
        char* ssn = get_ssn_from_session(sockfd);
        if (ssn == NULL) {
            return -1;
        }
        char* body = "<html><head><title>Info</title></head><body>";
        body += "<h1>Username: ";
        body += username;
        body += "</h1>";
        body += "<p>Email: ";
        body += email;
        body += "</p>";
        body += "<p>SSN: ";
        char* ssn_display = malloc(strlen(ssn) - 4);
        memcpy(ssn_display, ssn + 5, strlen(ssn) - 6);
        body += ssn_display;
        free(ssn_display);
        body += "</p>";
        body += "</body></html>";
        return send_response(sockfd, body);
    }