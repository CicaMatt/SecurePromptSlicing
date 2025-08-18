import java.util.HashMap;
import java.util.Scanner;

class User {
    String email;
    String passwordHash; // Simple representation for demonstration

    public User(String email, String password) {
        this.email = email;
        this.passwordHash = hashPassword(password);
    }

    private String hashPassword(String password) {
        return Integer.toString(password.hashCode());
    }
}

public class LoginSystem {

    private static HashMap<String, User> usersDatabase = new HashMap<>();
    private static String loggedInEmail = null;

    public static void main(String[] args) {
        // Sample user for demonstration
        usersDatabase.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = usersDatabase.get(email);
        if (user != null && user.passwordHash.equals(hashPassword(password))) {
            loggedInEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        User user = usersDatabase.get(loggedInEmail);
        if (user == null || !oldEmail.equals(user.email) || !user.passwordHash.equals(hashPassword(confirmPassword))) {
            System.out.println("Invalid old email or confirm password.");
            return;
        }

        if (usersDatabase.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        user.email = newEmail;
        usersDatabase.put(newEmail, user);
        usersDatabase.remove(oldEmail);

        loggedInEmail = newEmail; // Update the logged-in email
        System.out.println("Email changed successfully!");
    }

    private static String hashPassword(String password) {
        return Integer.toString(password.hashCode());
    }
}