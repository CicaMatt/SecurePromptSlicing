import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static Map<String, User> users = new HashMap<>();
    private static String loggedInEmail = null;

    public static void main(String[] args) {
        // Sample user for testing purposes
        addUser("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        
        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine();  // Consume newline

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
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void addUser(String email, String password) {
        users.put(email, new User(email, password));
    }

    private static void login(Scanner scanner) {
        if (loggedInEmail != null) {
            System.out.println("You are already logged in.");
            return;
        }

        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.getPassword().equals(password)) {
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

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String password = scanner.nextLine();

        User user = users.get(loggedInEmail);
        if (user != null && user.getPassword().equals(password) && oldEmail.equals(user.getEmail())) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            if (!newEmail.isEmpty() && !users.containsKey(newEmail)) {
                users.put(newEmail, user);
                users.remove(oldEmail);
                loggedInEmail = newEmail;
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Invalid or existing email.");
            }
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }

    static class User {
        private String email;
        private String password;

        public User(String email, String password) {
            this.email = email;
            this.password = password;
        }

        public String getEmail() {
            return email;
        }

        public String getPassword() {
            return password;
        }
    }
}