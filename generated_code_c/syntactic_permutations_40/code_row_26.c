#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "session.h"
#include "api_info.h"

void info(struct webnet_request *req, struct webnet_response *resp)
{
    struct session *sess;
    struct api_info *api;
    
    sess = get_session();
    api = get_api_info();

    char username[30];
    char email[50];
    int ssn;

    strcpy(username, sess->username);
    strcpy(email, sess->email);
    ssn = sess->ssn;

    send_response(req, resp, 200, "text/html", "<html><body>Username: %s<br/>Email:%s<br/>SSN: %d</body></html>", username, email, ssn);
}