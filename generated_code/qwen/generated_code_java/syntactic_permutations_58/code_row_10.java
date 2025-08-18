import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> users = new HashMap<>();
    private String loggedInUser = null;

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);
        
        // Adding a user for demonstration purposes
        system.users.put("user@example.com", "password123");
        
        while (true) {
            System.out.println("Options: login, changeEmail, logout, exit");
            String option = scanner.nextLine();

            switch (option.toLowerCase()) {
                case "login":
                    system.login(scanner);
                    break;
                case "changeemail":
                    system.changeEmail(scanner);
                    break;
                case "logout":
                    system.logout();
                    break;
                case "exit":
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("Please log in first.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter current password: ");
        String password = scanner.nextLine();

        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            // Check if the new email is already taken
            if (users.containsKey(newEmail)) {
                System.out.println("This email is already in use.");
                return;
            }

            users.put(newEmail, users.remove(oldEmail));
            loggedInUser = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid old email or password.");
        }
    }

    private void logout() {
        if (loggedInUser != null) {
            loggedInUser = null;
            System.out.println("Logged out successfully.");
        } else {
            System.out.println("No user is logged in.");
        }
    }
}