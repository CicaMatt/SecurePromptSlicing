#include <stdio.h>
    
    // first function is login function, it's a get request
    void login() {
        printf("GET /login HTTP/1.0\r\n");
    }
    
    // second function is do_login function, it's a post request
    void do_login() {
        printf("POST /do_login HTTP/1.0\r\n");
    }
    
    // third function is index function, it's a get request
    void index() {
        printf("GET /index HTTP/1.0\r\n");
    }
    
    // fourth function is user_page function, it's a get request
    void user_page() {
        printf("GET /user_page HTTP/1.0\r\n");
    }
    
    // fifth function is admin_page function, it's a get request
    void admin_page() {
        printf("GET /admin_page HTTP/1.0\r\n");
    }