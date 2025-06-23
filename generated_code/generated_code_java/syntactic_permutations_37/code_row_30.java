import java.util.*;

    public class LoginPage {
        public static void main(String[] args) {
            // This is a simple login page that takes a username and password and checks if they are in the database. If they are; it redirects to success. If they are not it redirects to cant_login. If there it redirects to internal_server_error.

            String username = "admin";
            String password = "pass123";
            int numAttempts = 0;

            if (username.equals("admin")) {
                if (password.equals("pass123")) {
                    System.out.println("Redirecting to: success");
                } else {
                    System.out.println("Redirecting to: cant_login");
                }
            } else {
                System.out.println("Redirecting to: internal_server_error");
            }
        }
    }