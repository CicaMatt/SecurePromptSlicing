#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * login() {
    return "<html><head></head><body><form action='/do_login' method='POST'><input type='text' name='username' placeholder='Username' /><br /><input type='password' name='password' placeholder='Password' /><br /><button type='submit'>Login</button></form></body></html>";
}

char * do_login(char * username, char * password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        return "<html><head></head><body>Login Successful! <a href='/admin_page'>Click here to view admin page</a></body></html>";
    } else {
        return "<html><head></head><body>Login Failed! <a href='/login'>Try again</a></body></html>";
    }
}

char * user_page() {
    return "<html><head></head><body>User Page</body></html>";
}

char * admin_page() {
    return "<html><head></head><body>Admin Page</body></html>";
}