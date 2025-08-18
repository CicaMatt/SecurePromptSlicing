import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginPage {

    private static Map<String, String> userDatabase = new HashMap<>();
    
    static {
        // Initial users for demonstration purposes.
        userDatabase.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Login to change your email:");
        System.out.print("Email: ");
        String loginEmail = scanner.nextLine();
        System.out.print("Password: ");
        String loginPassword = scanner.nextLine();

        if (authenticateUser(loginEmail, loginPassword)) {
            System.out.println("Authenticated successfully. Proceed to change email.");
            
            System.out.print("Old Email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("New Email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm Password: ");
            String confirmPassword = scanner.nextLine();

            if (changeUserEmail(oldEmail, newEmail, confirmPassword)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Please check your details and try again.");
            }
        } else {
            System.out.println("Authentication failed. Please check your credentials and try again.");
        }

        scanner.close();
    }

    private static boolean authenticateUser(String email, String password) {
        return userDatabase.containsKey(email) && userDatabase.get(email).equals(password);
    }

    private static boolean changeUserEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!userDatabase.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return false;
        }
        
        if (!userDatabase.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password for the provided old email.");
            return false;
        }
        
        if (newEmail.isEmpty() || newEmail.equals(oldEmail)) {
            System.out.println("New email must be different and not empty.");
            return false;
        }

        userDatabase.put(newEmail, userDatabase.get(oldEmail));
        userDatabase.remove(oldEmail);
        return true;
    }
}