import java.util.HashMap;
import java.util.Scanner;

public class SimpleLogin {
    private static HashMap<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Initialize sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.exit(0);
                default:
                    System.out.println("Invalid choice.");
            }
        }
    }

    private static void login(Scanner scanner) {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).password.equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUserEmail);

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the logged in account.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Enter confirm password: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(user.password)) {
            System.out.println("Incorrect password.");
            return;
        }

        // Check if the new email already exists
        if (users.containsKey(newEmail)) {
            System.out.println("New email is already in use.");
            return;
        }

        // Update user email
        users.remove(oldEmail);
        user.email = newEmail;
        users.put(newEmail, user);

        loggedInUserEmail = newEmail;
        System.out.println("Email changed successfully.");
    }
}

class User {
    String email;
    String password;

    User(String email, String password) {
        this.email = email;
        this.password = password;
    }
}