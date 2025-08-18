import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        // Initial user setup for demonstration
        users.put("user@example.com", "password123");
        
        System.out.println("Welcome to the Email Change System!");
        while (true) {
            if (loggedInUser == null) {
                login(scanner);
            } else {
                changeEmail(scanner);
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("You are not logged in with the provided email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password to verify ownership of the old email: ");
        String confirmPassword = scanner.nextLine();
        
        if (users.get(oldEmail).equals(confirmPassword)) {
            users.put(newEmail, users.remove(oldEmail));
            loggedInUser = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }
}