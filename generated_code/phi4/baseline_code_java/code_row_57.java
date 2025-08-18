import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginPage {
    private static Map<String, String> usersDatabase = new HashMap<>();
    
    public static void main(String[] args) {
        // Initial user setup for demonstration purposes
        usersDatabase.put("user@example.com", "password123");
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        
        if (!usersDatabase.containsKey(email)) {
            System.out.println("Email not found.");
            return;
        }
        
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();
        
        if (!usersDatabase.get(email).equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }
        
        System.out.print("Enter your old email (current email): ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(email)) {
            System.out.println("Old email does not match the current email.");
            return;
        }
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (usersDatabase.containsKey(newEmail)) {
            System.out.println("New email is already in use by another user.");
            return;
        }
        
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        
        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect confirm password.");
            return;
        }
        
        // Update the email
        usersDatabase.remove(oldEmail);
        usersDatabase.put(newEmail, password);
        
        System.out.println("Email changed successfully!");
    }
}