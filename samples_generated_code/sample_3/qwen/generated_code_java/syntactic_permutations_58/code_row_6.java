import java.util.Scanner;
import java.util.HashMap;

public class LoginSystem {
    private HashMap<String, String> userCredentials = new HashMap<>();
    private HashMap<String, String> userEmails = new HashMap<>();
    private boolean isLoggedIn = false;
    private String loggedInUsername;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.userCredentials.put("user1", "password123");
        system.userEmails.put("user1", "user1@example.com");

        Scanner scanner = new Scanner(System.in);
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine();

            switch (choice) {
                case 1:
                    system.login(scanner);
                    break;
                case 2:
                    if (system.isLoggedIn) {
                        system.changeEmail(scanner);
                    } else {
                        System.out.println("Please log in first.");
                    }
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(username) && userCredentials.get(username).equals(password)) {
            isLoggedIn = true;
            loggedInUsername = username;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your password to confirm: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(loggedInUsername) && userCredentials.get(loggedInUsername).equals(password) && userEmails.get(loggedInUsername).equals(oldEmail)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            userEmails.put(loggedInUsername, newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }
}