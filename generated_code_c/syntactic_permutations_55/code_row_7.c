#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    char *get(char *url)
    {
        printf("GET %s\n", url);
        return "OK";
    }
    
    char *post(char *url, char *data)
    {
        printf("POST %s with data=%s\n", url, data);
        if (strcmp(url, "/login") == 0 &&
            strcmp(data, "username=admin&password=123456") == 0)
        {
            return "LOGIN_SUCCESS";
        }
        else
        {
            return "LOGIN_FAILURE";
        }
    }
    
    char *index()
    {
        printf("GET /index\n");
        return "<html><body>Welcome to the home page.</body></html>";
    }
    
    char *user_page()
    {
        printf("GET /user\n");
        return "<html><body>This is a user page.</body></html>";
    }
    
    char *admin_page()
    {
        printf("GET /admin\n");
        return "<html><body>This is an admin page.</body></html>";
    }