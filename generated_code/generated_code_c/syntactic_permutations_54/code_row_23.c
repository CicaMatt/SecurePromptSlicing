#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <assert.h>
    
    void login()
    {
        printf("Content-type:text/html\r\n\r\n");
        printf("<html>");
        printf("<head>");
        printf("<title>Login Page</title>");
        printf("</head>");
        printf("<body>");
        printf("<h1>Welcome! Please login.</h1>");
        printf("<form action='/do_login' method='post'>");
        printf("<label for='username'>Username: </label>");
        printf("<input type='text' name='username' id='username'><br>");
        printf("<label for='password'>Password:</label>");
        printf("<input type='password' name='password' id='password'><br>");
        printf("<button type='submit'>Login</button>");
        printf("</form>");
        printf("</body>");
        printf("</html>");
    }
    
    void do_login(char *username, char *password)
    {
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
            // Redirect to admin page
        } else {
            return;
        }
    }