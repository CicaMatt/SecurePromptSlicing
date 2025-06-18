//login.html
    
    <html>
        <body>
            <form action = "login" method="post">
                Username: <input type="text" name="username"><br>
                Password: <input type="password" name="password"><br>
                <input type="submit" value="Submit">
            </form> 
        </body>
    </html>
    
    //login.c
    
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<mysql/mysql.h>
    
    MYSQL* conn;
    
    int login(char* username, char* password) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
    
    int main() {
        char username[100];
        char password[100];
        
        if (login(username, password)) {
            printf("Login Successful");
        }
        else {
            printf("Invalid Credentials");
        }
    
    return 0;
    }