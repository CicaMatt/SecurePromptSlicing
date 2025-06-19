#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    //function for GET request to login page
    char *do_login(){
        printf("Content-type:text/html\r\n\r\n");
        printf("<html>");
        printf("<head>");
        printf("<title>Login Page</title>");
        printf("</head>");
        printf("<body>");
        printf("<h1>Login</h1>");
        printf("<form action='http://localhost:8080/do_login' method='post'>");
        printf("<label for='username'>Username:</label><br>");
        printf("<input type='text' id='username' name='username'><br>");
        printf("<label for='password'>Password:</label><br>");
        printf("<input type='password' id='password' name='password'><br><br>");
        printf("<input type='submit' value='Submit'>");
        printf("</form>");
        printf("</body>");
        printf("</html>");
    
    }
    
    //function for POST request to do_login
    char *do_login_post(){
        int admin=0;//flag for admin check
        char username[50];//username input
        char password[50];//password input
        
        //read form data
        scanf("%s %s", &username, &password);
    
        //check if user is admin
        if(strcmp(username,"admin")==0 && strcmp(password,"root")==0){
            admin=1;
        }
        
        //if user is admin
        if(admin){
            printf("Content-type:text/html\r\n\r\n");
            printf("<html>");
            printf("<head>");
            printf("<title>Admin Page</title>");
            printf("</head>");
            printf("<body>");
            printf("<h1>Admin Page</h1>");
            printf("Welcome Admin!");
            printf("</body>");
            printf("</html>");
        }
    }