import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private Map<String, String> userEmails = new HashMap<>();

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.initializeUsers();
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username:");
        String username = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Login successful. Would you like to change your email? (yes/no)");
            String response = scanner.nextLine();
            if ("yes".equalsIgnoreCase(response)) {
                system.changeEmail(scanner, username);
            }
        } else {
            System.out.println("Login failed.");
        }
    }

    private void initializeUsers() {
        userCredentials.put("user1", "password1");
        userEmails.put("user1", "user1@example.com");
    }

    private boolean login(String username, String password) {
        return userCredentials.containsKey(username) && userCredentials.get(username).equals(password);
    }

    private void changeEmail(Scanner scanner, String username) {
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String password = scanner.nextLine();

        if (userEmails.containsKey(username) && userEmails.get(username).equals(oldEmail) && userCredentials.get(username).equals(password)) {
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();
            userEmails.put(username, newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Old email or password is incorrect. Email not changed.");
        }
    }
}