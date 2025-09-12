import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUser = null;

    public LoginSystem() {
        // Sample user data
        userCredentials.put("user1", "password1");
        userCredentials.put("user2", "password2");
    }

    public void login(String username, String password) {
        if (userCredentials.containsKey(username) && userCredentials.get(username).equals(password)) {
            loggedInUser = username;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    public void changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUser == null) {
            System.out.println("Please log in first.");
            return;
        }

        if (!userCredentials.containsKey(loggedInUser)) {
            System.out.println("User not found.");
            return;
        }

        if (!userCredentials.get(loggedInUser).equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        // Assuming the old email is the username for simplicity
        if (!loggedInUser.equals(oldEmail)) {
            System.out.println("Old email does not match.");
            return;
        }

        userCredentials.remove(loggedInUser);
        userCredentials.put(newEmail, password);
        loggedInUser = newEmail;
        System.out.println("Email changed successfully.");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
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
                    System.out.print("Enter username: ");
                    String username = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String password = scanner.nextLine();
                    loginSystem.login(username, password);
                    break;
                case 2:
                    if (loginSystem.loggedInUser == null) {
                        System.out.println("Please log in first.");
                        continue;
                    }
                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Enter password: ");
                    password = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    loginSystem.changeEmail(oldEmail, password, newEmail);
                    break;
                case 3:
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid option.");
            }
        }
    }
}