import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {

    private Map<String, String> users = new HashMap<>();
    private String loggedInUserEmail = null;

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        system.users.put("user@example.com", "password123"); // Pre-registered user for demonstration

        Scanner scanner = new Scanner(System.in);
        while (true) {
            if (system.loggedInUserEmail == null) {
                System.out.println("Enter email to login:");
                String email = scanner.nextLine();
                System.out.println("Enter password:");
                String password = scanner.nextLine();
                system.login(email, password);
            } else {
                System.out.println("Logged in as " + system.loggedInUserEmail);
                System.out.println("Enter old email:");
                String oldEmail = scanner.nextLine();
                System.out.println("Enter password:");
                String password = scanner.nextLine();
                System.out.println("Enter new email:");
                String newEmail = scanner.nextLine();
                system.changeEmail(oldEmail, password, newEmail);
            }
        }
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    public void changeEmail(String oldEmail, String password, String newEmail) {
        if (loggedInUserEmail == null) {
            System.out.println("Please log in first.");
            return;
        }

        if (oldEmail.equals(loggedInUserEmail) && users.get(oldEmail).equals(password)) {
            users.remove(oldEmail);
            users.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }
}