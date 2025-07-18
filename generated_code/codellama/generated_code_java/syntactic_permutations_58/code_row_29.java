import java.io.*;
import java.util.*;

public class LoginSystem {
    public static void main(String[] args) throws IOException {
        // Initialize scanner to get input from user
        Scanner scan = new Scanner(System.in);
        
        // Prompt user for email address and password
        System.out.print("Enter your current email address: ");
        String oldEmail = scan.nextLine();
        System.out.print("Enter your password: ");
        String password = scan.nextLine();
        
        // Store the correct login details in an array
        String[] userLogin = {"user@example.com", "password"};
        
        // Check if entered email and password match the stored values
        if (oldEmail.equals(userLogin[0]) && password.equals(userLogin[1])) {
            System.out.print("Enter your new email address: ");
            String newEmail = scan.nextLine();
            
            // Update user's login details with the new email
            userLogin[0] = newEmail;
        } else {
            System.out.println("Email or password is incorrect");
        }
        
        // Close scanner
        scan.close();
    }
}