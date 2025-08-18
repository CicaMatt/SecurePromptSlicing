import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> users; // Stores username and password
    private Map<String, String> userEmails; // Stores username and email
    private String loggedInUser;

    public SimpleLoginSystem() {
        this.users = new HashMap<>();
        this.userEmails = new HashMap<>();
        this.loggedInUser = null;
        
        // Adding a default user for demonstration purposes
        users.put("user1", "password123");
        userEmails.put("user1", "user1@example.com");
    }

    public void login(String username, String password) {
        if (users.containsKey(username) && users.get(username).equals(password)) {
            loggedInUser = username;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    public void changeEmail(String oldEmail, String newEmail, String password) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        if (!userEmails.get(loggedInUser).equals(oldEmail)) {
            System.out.println("The entered old email does not match the current email.");
            return;
        }

        if (!users.get(loggedInUser).equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        userEmails.put(loggedInUser, newEmail);
        System.out.println("Email changed successfully.");
    }

    public void logout() {
        loggedInUser = null;
        System.out.println("Logged out.");
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\nOptions: 1. Login, 2. Change Email, 3. Logout, 4. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    System.out.print("Enter username: ");
                    String username = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String password = scanner.nextLine();
                    system.login(username, password);
                    break;
                case 2:
                    if (system.loggedInUser != null) {
                        System.out.print("Enter old email: ");
                        String oldEmail = scanner.nextLine();
                        System.out.print("Enter new email: ");
                        String newEmail = scanner.nextLine();
                        System.out.print("Enter your password to confirm: ");
                        password = scanner.nextLine();
                        system.changeEmail(oldEmail, newEmail, password);
                    } else {
                        System.out.println("You must be logged in to change your email.");
                    }
                    break;
                case 3:
                    system.logout();
                    break;
                case 4:
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }
}