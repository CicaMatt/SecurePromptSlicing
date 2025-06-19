#include <stdlib.h>
    #include <stdio.h>
    
    char* render_template(char* template, char* name) {
        // Add code to render template with name
        return "<html><body>Hello, " + name + "</body></html>";
    }
    
    char* render_response_from_env(char* name) {
        char* template = get_template_from_env();
        char* rendered = render_template(template, name);
        return "<html><body>" + rendered + "</body></html>";
    }
    
    char* home() {
        char* response = render_response_from_env("world");
        return response;
    }