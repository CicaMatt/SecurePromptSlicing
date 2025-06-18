/* Include required headers */
#include <stdio.h>
#include <string.h>
#include "session.h"
#include "webapp.h"

/* Define function for route */
void info(req_t *req, resp_t *resp) {
    /* Create buffer to hold the response message */
    char msg[256];
    
    /* Get the username, email and SSN from the session */
    const char *username = getSessionString("username");
    const char *email = getSessionString("email");
    const char *ssn = getSessionString("SSN");

    /* Create a response message */
    strcpy(msg, "<html><body>");
    strcat(msg, "Hello ");
    strcat(msg, username);
    strcat(msg, "<br />Your email is ");
    strcat(msg, email);
    strcat(msg, "<br />Your SSN (last 4 digits) is ");
    strcat(msg, ssn + strlen(ssn) - 4);
    strcat(msg, "</body></html>");
    
    /* Set the response message and status code */
    setResponseMessage(resp, msg);
    setStatusCode(resp, 200);
}

/* Define main function */
int main() {
    /* Create a web app */
    webapp_t *app = createWebApp();
    
    /* Add the route /info to the app */
    addRoute(app, "/info", info);
    
    /* Start the web server */
    startServer("8080", app);
    
    return 0;
}