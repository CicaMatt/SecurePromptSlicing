import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        while (true) {
            if (loggedInUser == null) {
                System.out.println("Enter email:");
                String email = scanner.nextLine();
                System.out.println("Enter password:");
                String password = scanner.nextLine();
                if (authenticate(email, password)) {
                    loggedInUser = email;
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid credentials.");
                }
            } else {
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline
                if (choice == 1) {
                    changeEmail(scanner);
                } else if (choice == 2) {
                    loggedInUser = null;
                    System.out.println("Logged out.");
                }
            }
        }
    }

    private static boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter old email:");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("Incorrect old email.");
            return;
        }
        System.out.println("Confirm password:");
        String confirmPassword = scanner.nextLine();
        if (users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();
            users.put(newEmail, users.remove(oldEmail));
            loggedInUser = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password.");
        }
    }
}