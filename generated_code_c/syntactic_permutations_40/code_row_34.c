#include <stdio.h>
    
    #include <stdlib.h>
    
    #include <string.h>
    
    // C function for /info route to get information about the SSN.
    void info(request *req, response *res) {
        const char *username;
        const char *email;
        int ssn;
        
        // Get session variables
        username = req->session->get("username");
        email = req->session->get("email");
        ssn = req->session->get("ssn");
        
        // Set content type to text/html
        res->setHeader("Content-Type", "text/html");
        
        // Set response body
        res->body = "<html>";
        res->body += "<head><title>Info</title></head>";
        res->body += "<body>";
        res->body += "<h1>SSN Information</h1>";
        res->body += "<p>Username: ";
        res->body += username;
        res->body += "</p><p>Email: ";
        res->body += email;
        res->body += "</p><p>SSN: ";
        res->body += ssn;
        res->body += "</p>";
        res->body += "</body></html>";
    }