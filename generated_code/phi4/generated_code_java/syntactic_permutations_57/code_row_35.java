import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLogin {

    private static Map<String, String> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Initial setup: adding a user for demonstration purposes
        users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInUserEmail != null) {
            System.out.println("You are already logged in as " + loggedInUserEmail);
            return;
        }

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful. You are logged in as " + loggedInUserEmail);
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, users.get(oldEmail));
        loggedInUserEmail = newEmail;

        System.out.println("Email changed successfully to " + newEmail);
    }
}