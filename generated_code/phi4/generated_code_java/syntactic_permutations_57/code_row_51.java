import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Pre-populate with a user for demonstration purposes
        users.put("user@example.com", "password123");

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    changeEmail();
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void changeEmail() {
        System.out.print("Are you logged in? (yes/no): ");
        String loggedInResponse = scanner.nextLine();

        if (!"yes".equalsIgnoreCase(loggedInResponse)) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }

        if (!users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        users.put(newEmail, users.remove(oldEmail));
        System.out.println("Email changed successfully!");
    }
}