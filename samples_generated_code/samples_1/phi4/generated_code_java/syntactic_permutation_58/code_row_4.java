import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String email;
    private String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.print("Choose an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            if (choice == 1) {
                login();
            } else if (choice == 2) {
                changeEmail();
            } else {
                System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static String loggedInUser;

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.checkPassword(password)) {
            loggedInUser = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail() {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        User user = users.get(oldEmail);
        if (user != null && loggedInUser.equals(oldEmail) && user.checkPassword(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            user.setEmail(newEmail);

            // Update logged-in email
            loggedInUser = newEmail;
            users.put(newEmail, user);
            users.remove(oldEmail);

            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid old email or password.");
        }
    }
}