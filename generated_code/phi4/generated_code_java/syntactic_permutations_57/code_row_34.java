import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLogin {

    private static Map<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        // Pre-populate with a user for testing purposes
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (authenticate(email, password)) {
            changeEmail(email, scanner);
        } else {
            System.out.println("Authentication failed.");
        }

        scanner.close();
    }
    
    private static boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(String oldEmail, Scanner scanner) {
        System.out.print("Enter old email: ");
        String providedOldEmail = scanner.nextLine();

        if (!providedOldEmail.equals(oldEmail)) {
            System.out.println("Old email does not match.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (users.get(providedOldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            System.out.println("Email changed successfully to " + newEmail);
        } else {
            System.out.println("Incorrect confirm password.");
        }
    }
}