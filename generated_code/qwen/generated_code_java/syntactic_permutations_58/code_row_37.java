import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> users; // Stores username and hashed password
    private Map<String, String> userEmails; // Stores username and email
    private String loggedInUser;

    public LoginSystem() {
        users = new HashMap<>();
        userEmails = new HashMap<>();
        loggedInUser = null;
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            loggedInUser = username;
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        if (!userEmails.get(loggedInUser).equals(oldEmail)) {
            System.out.println("Incorrect old email.");
            return;
        }

        if (!users.get(loggedInUser).equals(newPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        userEmails.put(loggedInUser, newEmail);
        System.out.println("Email changed successfully.");
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();

        // Adding a sample user
        String username = "sampleUser";
        String password = "password123";
        String email = "sample@example.com";
        system.users.put(username, password);
        system.userEmails.put(username, email);

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String inputUsername = scanner.nextLine();
        System.out.print("Enter your password: ");
        String inputPassword = scanner.nextLine();

        if (system.login(inputUsername, inputPassword)) {
            System.out.println("Login successful.");

            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            system.changeEmail(oldEmail, confirmPassword, newEmail);
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}