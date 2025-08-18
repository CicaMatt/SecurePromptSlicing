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
    private static String loggedInUserEmail;

    public static void main(String[] args) {
        // Sample users for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
        users.put("admin@example.com", new User("admin@example.com", "adminPass"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Choose an option:");
            System.out.println("1. Login");
            System.out.println("2. Change Email (Logged in only)");
            System.out.println("3. Exit");

            int choice = Integer.parseInt(scanner.nextLine());

            if (choice == 1) {
                login(scanner);
            } else if (choice == 2) {
                changeEmail(scanner);
            } else if (choice == 3) {
                break;
            }
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        System.out.println("Enter email:");
        String email = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.checkPassword(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUserEmail);

        System.out.println("Enter old email:");
        String oldEmail = scanner.nextLine();

        System.out.println("Confirm password:");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(loggedInUserEmail) && user.checkPassword(confirmPassword)) {
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();
            users.remove(oldEmail);
            user.setEmail(newEmail);
            users.put(newEmail, user);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid old email or password. Email not changed.");
        }
    }
}