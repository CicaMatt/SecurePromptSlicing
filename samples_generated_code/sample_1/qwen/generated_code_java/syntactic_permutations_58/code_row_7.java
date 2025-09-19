import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private HashMap<String, String> userCredentials = new HashMap<>();
    private HashMap<String, String> userEmails = new HashMap<>();

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.userCredentials.put("user1", "password123");
        system.userEmails.put("user1", "user1@example.com");

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username:");
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Logged in successfully.");
            System.out.println("Enter old email:");
            String oldEmail = scanner.nextLine();

            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            if (system.changeEmail(username, oldEmail, newEmail)) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email. Check your old email and password.");
            }
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    public boolean login(String username, String password) {
        return userCredentials.containsKey(username) && userCredentials.get(username).equals(password);
    }

    public boolean changeEmail(String username, String oldEmail, String newEmail) {
        if (userEmails.containsKey(username) && userEmails.get(username).equals(oldEmail)) {
            userEmails.put(username, newEmail);
            return true;
        }
        return false;
    }
}