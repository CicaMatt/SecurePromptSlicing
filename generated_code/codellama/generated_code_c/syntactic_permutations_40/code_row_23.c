#include <stdio.h>
#include "stdlib.h"
#include "string.h"

//function to get info
void info(request_t *req, response_t *res) {
    //get session variables
    char *username = req->session->get("username");
    char *email = req->session->get("email");
    char *ssn = req->session->get("ssn");
    
    //create page with username, email and last 4 digits of ssn
    char *page = "<html><head></head><body>";
    strcat(page, "<p>Username: ");
    strcat(page, username);
    strcat(page, "</p>");
    strcat(page, "<p>Email: ");
    strcat(page, email);
    strcat(page, "</p>");
    strcat(page, "<p>SSN: ");
    int length = strlen(ssn) - 4;
    char *last_four = ssn + length;
    strcat(page, last_four);
    strcat(page, "</p></body></html>");
    
    //set response body to page
    res->setBody(page);
}