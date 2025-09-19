import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> users = new HashMap<>();
    private String loggedInUserEmail;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.users.put("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    if (system.isLoggedIn()) {
                        system.changeEmail(scanner);
                    } else {
                        System.out.println("You need to be logged in to change your email.");
                    }
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
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Incorrect email or password.");
        }
    }

    private boolean isLoggedIn() {
        return loggedInUserEmail != null;
    }

    private void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String password = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (loggedInUserEmail.equals(oldEmail) && users.get(loggedInUserEmail).equals(password)) {
            users.remove(loggedInUserEmail);
            users.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }
}