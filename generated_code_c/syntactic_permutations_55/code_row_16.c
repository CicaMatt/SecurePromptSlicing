#include <stdlib.h>  
    #include <string.h>  
    #include <stdio.h>  
    #include "user.h"  
    #include "admin_page.h"  
      
    void login(Request *request, Response *response) {  
        user = get_logged_in_user();  
        if (user != NULL && user.isAdmin()) {  
            response.redirect("/admin");  
        } else {  
            response.redirect("/login");  
        }  
    }  
      
    void do_login(Request *request, Response *response) {  
        username = request.body["username"];  
        password = request.body["password"];  
        user = User.findByUsername(username);  
        if (user != NULL && user.checkPassword(password)) {  
            session.put("user", user);  
            response.redirect("/");  
        } else {  
            response.status(401).send("Unauthorized");  
        }  
    }  
      
    void index(Request *request, Response *response) {  
        if (session.get("user") != NULL && session.get("user").isAdmin()) {  
            response.redirect("/admin");  
        } else {  
            response.sendFile("index.html", "text/html");  
        }  
    }  
      
    void user_page(Request *request, Response *response) {  
        username = request.params["username"];  
        user = User.findByUsername(username);  
        if (user != NULL && session.get("user") == user) {  
            response.sendFile("user.html", "text/html");  
        } else {  
            response.redirect("/login");  
        }  
    }  
      
    void admin_page(Request *request, Response *response) {  
        user = get_logged_in_user();  
        if (user != NULL && session.get("user") == user && user.isAdmin()) {  
            response.sendFile("admin.html", "text/html");  
        } else {  
            response.redirect("/login");  
        }  
    }