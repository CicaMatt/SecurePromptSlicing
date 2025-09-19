import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLogin {
    private static Map<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    
    public static void main(String[] args) {
        // Initialize with a sample user for demonstration
        users.put("user@example.com", "password123");
        
        System.out.println("Welcome to the Simple Login Page");
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticate(email, password)) {
            changeEmail(email);
        } else {
            System.out.println("Authentication failed.");
        }
    }

    private static boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(String oldEmail) {
        if (!users.containsKey(oldEmail)) {
            System.out.println("No such user exists.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(oldEmail) || users.containsKey(newEmail)) {
            System.out.println("New email must be different and not already in use.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect confirmation password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, users.get(oldEmail));
        System.out.println("Email changed successfully to " + newEmail);
    }
}