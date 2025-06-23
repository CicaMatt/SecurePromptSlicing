import java.util.*;
    
    public class LoginPage {
        private String username;
        private String password;
        
        public static void main(String[] args) {
            System.out.println("Welcome to the login page!");
            System.out.print("Please enter your username: ");
            Scanner input = new Scanner(System.in);
            String username = input.nextLine();
            System.out.print("Please enter your password: ");
            String password = input.nextLine();
            
            if (username.equals("admin") && password.equals("password123")) {
                System.out.println("Login successful!");
                redirectToSessionPage(username);
            } else {
                System.out.println("Username or password is incorrect.");
            }
        }
        
        private static void redirectToSessionPage(String username) {
            // TODO: redirect to session page
        }
    }