import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInEmail = null;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.userCredentials.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    if (system.loggedInEmail != null) {
                        system.changeEmail(scanner);
                    } else {
                        System.out.println("Please log in first.");
                    }
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();

            // Remove the old email and add the new one
            String currentPassword = userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, currentPassword);
            loggedInEmail = newEmail;

            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid old email or password. Email change failed.");
        }
    }
}