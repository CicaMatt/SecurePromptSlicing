#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Do_login function
int do_login(char* username, char* password) {
    //Check if the user and pass are correct
    if (username == "admin" && password == "admin") {
        //Set the session username to admin
        set_session_username("admin");
        return 1;
    } else {
        return 0;
    }
}

//set_session_username function
void set_session_username(char* username) {
    //Set the session username to the username
    session_username = username;
}

//login page code
int login() {
    //print the form
    printf("<form><input type='text' name='username' placeholder='Username'><br>");
    printf("<input type='password' name='password' placeholder='Password'><br>");
    printf("<button type='submit'>Login</button></form>");
}

//secret page code
int secret_page() {
    //print the secret message
    printf("Secret settings");
}