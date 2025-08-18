import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static Map<String, String> userCredentials = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        userCredentials.put("user@example.com", "password123");

        System.out.println("Welcome to the Simple Login System");
        while (true) {
            if (loggedInUserEmail == null) {
                System.out.println("\nPlease log in.");
                login(scanner);
            } else {
                System.out.println("\nYou are logged in as: " + loggedInUserEmail);
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        changeEmail(scanner);
                        break;
                    case 2:
                        logout();
                        break;
                    default:
                        System.out.println("Invalid option. Please try again.");
                }
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password. Please try again.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your password to confirm: ");
        String password = scanner.nextLine();

        if (loggedInUserEmail.equals(oldEmail) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            userCredentials.remove(loggedInUserEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email change failed.");
        }
    }

    private static void logout() {
        loggedInUserEmail = null;
        System.out.println("You have been logged out.");
    }
}