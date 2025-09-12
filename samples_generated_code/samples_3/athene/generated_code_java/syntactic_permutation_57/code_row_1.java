import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeService {
    private HashMap<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public void login() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void changeEmail() {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser) || !users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Invalid old email or password.");
            return;
        }

        users.put(newEmail, users.remove(oldEmail));
        loggedInUser = newEmail;
        System.out.println("Email changed successfully!");
    }

    public static void main(String[] args) {
        EmailChangeService service = new EmailChangeService();
        Scanner scanner = new Scanner(System.in);

        // Pre-populate some users for testing
        service.users.put("user1@example.com", "password1");
        service.users.put("user2@example.com", "password2");

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    service.login();
                    break;
                case 2:
                    service.changeEmail();
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }
}