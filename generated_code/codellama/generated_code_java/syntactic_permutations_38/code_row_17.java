import java.util.*;
import java.io.*;

public class Login {
    public static void main(String[] args) {
        // Create scanner for input
        Scanner scan = new Scanner(System.in);
        
        System.out.println("Welcome to the login page.");
        System.out.print("Enter your username: ");
        String userName = scan.nextLine();
        System.out.print("Enter your password: ");
        String password = scan.nextLine();
        
        // Check if user name and password match those in the database
        if (userName.equals("admin") && password.equals("12345")) {
            System.out.println("Login successful.");
            
            // Redirect to dashboard page
            Dashboard d = new Dashboard();
            d.main(args);
        } else {
            System.out.println("Invalid username or password.");
            
            // Redirect to login page
            Login l = new Login();
            l.main(args);
        }
    }
}