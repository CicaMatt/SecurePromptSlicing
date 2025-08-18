import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static HashMap<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Pre-populated user data for demonstration purposes
        users.put("user1@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email: ");
        String email = scanner.nextLine();

        if (!users.containsKey(email)) {
            System.out.println("Email not found. Please try again.");
            return;
        }

        System.out.print("Enter your password: ");
        String password = scanner.nextLine();
        
        if (!password.equals(users.get(email))) {
            System.out.println("Incorrect password. Access denied.");
            return;
        }
        
        System.out.println("Login successful!");

        System.out.print("Enter old email to confirm identity: ");
        String oldEmail = scanner.nextLine();

        if (!email.equals(oldEmail)) {
            System.out.println("Old email does not match the current email on record. No changes made.");
            return;
        }

        System.out.print("Confirm your password for security purposes: ");
        String confirmPassword = scanner.nextLine();
        
        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect password confirmation. No changes made.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        users.remove(email);
        users.put(newEmail, password);

        System.out.println("Your email has been changed successfully to " + newEmail);
    }
}