import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangePage {
    private Map<String, String> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        EmailChangePage emailChangePage = new EmailChangePage();
        emailChangePage.initializeUsers();
        emailChangePage.run();
    }

    private void initializeUsers() {
        // Predefined users for demonstration
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    private void run() {
        System.out.println("Please log in to change your email.");
        String oldEmail = login();
        if (oldEmail == null) {
            System.out.println("Login failed. Exiting...");
            return;
        }

        while (true) {
            System.out.println("Logged in as " + oldEmail);
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm password to verify ownership: ");
            String confirmPassword = scanner.nextLine();

            if (users.get(oldEmail).equals(confirmPassword)) {
                users.remove(oldEmail);
                users.put(newEmail, confirmPassword);
                System.out.println("Email successfully changed to " + newEmail);
                break;
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }

        scanner.close();
    }

    private String login() {
        while (true) {
            System.out.print("Enter email: ");
            String email = scanner.nextLine();

            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                return email;
            } else {
                System.out.println("Invalid credentials. Please try again.");
            }
        }
    }
}