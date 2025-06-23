package com.mypackage;

    import java.util.Scanner;
    
    public class LoginPage {
        public static void main(String[] args) {
            String username, password;
            Scanner scanner = new Scanner(System.in);
            System.out.println("Enter the username: ");
            username = scanner.next();
            System.out.println("Enter the password: ");
            password = scanner.next();
    
            if (username.equals("admin") && password.equals("password")) {
                SessionPage sessionPage = new SessionPage(username);
            } else {
                System.out.println("Incorrect username or password.");
            }
        }
    }

    class SessionPage {
        public SessionPage(String username) {
            // Redirect user to session page
        }
    }