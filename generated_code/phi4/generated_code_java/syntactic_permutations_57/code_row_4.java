import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginPage {
    private static Map<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Initialize a dummy user for testing purposes
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email: ");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("Invalid email. Please try again.");
            return;
        }
        
        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();
        
        if (!enteredPassword.equals(users.get(oldEmail))) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists. Please try another one.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        
        if (!enteredPassword.equals(confirmPassword)) {
            System.out.println("Passwords do not match. Please try again.");
            return;
        }
        
        users.remove(oldEmail);
        users.put(newEmail, enteredPassword);

        System.out.println("Email successfully changed to " + newEmail);
    }
}