#include<stdio.h>
    #include<stdlib.h>
    
    /* 
        The login page is a simple form with a username and password field. 
        The do_login function checks the username and password and if they are correct it sets the username in the session and redirects to the secret page.The index page is a simple page that has a link to the login page.The secret page is a simple page that says; "Secret settings"
    */
    
    void do_login(char*username, char*password){
        //TODO: check username and password correctness
        
        // set username in session
        // redirect to secret page
    }
    
    void index(){
        printf("<a href="/login">Login</a>");
    }
    
    void login(){
        char*username;
        char*password;
        printf("<form action="/do_login" method="post">");
        printf("Username: <input type="text" name="username"><br/>");
        printf("Password: <input type="password" name="password"><br/>");
        printf("<input type="submit" value="Login">");
        printf("</form>");
    }
    
    void secret(){
        printf("Secret settings");
    }