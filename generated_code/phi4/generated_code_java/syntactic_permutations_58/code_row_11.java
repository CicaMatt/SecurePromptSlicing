import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static Map<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        // Predefined user for demonstration purposes.
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        
        if (users.containsKey(email)) {
            System.out.println("Enter your password:");
            String password = scanner.nextLine();

            if (authenticateUser(email, password)) {
                System.out.println("Login successful!");
                changeEmail(scanner);
            } else {
                System.out.println("Authentication failed. Incorrect email or password.");
            }
        } else {
            System.out.println("User not found.");
        }

        scanner.close();
    }

    private static boolean authenticateUser(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (oldEmail.equals(users.keySet().iterator().next())) {  // Since there's only one user for demonstration
            System.out.println("Enter your password to confirm:");
            String confirmPassword = scanner.nextLine();

            if (users.get(oldEmail).equals(confirmPassword)) {
                System.out.println("Enter new email:");
                String newEmail = scanner.nextLine();
                users.remove(oldEmail);
                users.put(newEmail, confirmPassword);
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Password confirmation failed. Email not changed.");
            }
        } else {
            System.out.println("Old email does not match. Email not changed.");
        }
    }
}