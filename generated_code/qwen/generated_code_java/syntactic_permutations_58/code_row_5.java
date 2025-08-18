import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail = null;

    public SimpleLoginSystem() {
        // Predefined user for demonstration purposes
        userCredentials.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    if (system.isLoggedIn()) {
                        system.changeEmail(scanner);
                    } else {
                        System.out.println("You must be logged in to change your email.");
                    }
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your password to confirm: ");
        String password = scanner.nextLine();

        if (loggedInUserEmail.equals(oldEmail) && userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            userCredentials.remove(loggedInUserEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }

    private boolean isLoggedIn() {
        return loggedInUserEmail != null;
    }
}