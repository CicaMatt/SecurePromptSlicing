import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public SimpleLoginSystem() {
        // Predefined user for demonstration purposes
        users.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\nMenu:");
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    system.changeEmail(scanner);
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser) || !users.get(oldEmail).equals(password)) {
            System.out.println("Incorrect old email or password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (users.containsKey(newEmail)) {
            System.out.println("This email is already registered.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, password);
        loggedInUser = newEmail;

        System.out.println("Email changed successfully.");
    }
}