import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    
    private static HashMap<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Initialize a user for testing
        users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            if (loggedInUserEmail == null) {
                System.out.println("Choose an option: 1. Login, 2. Exit");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        login();
                        break;
                    case 2:
                        System.exit(0);
                        break;
                    default:
                        System.out.println("Invalid option.");
                }
            } else {
                System.out.println("Choose an option: 1. Change Email, 2. Logout");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        changeEmail();
                        break;
                    case 2:
                        logout();
                        break;
                    default:
                        System.out.println("Invalid option.");
                }
            }
        }
    }

    private static void login() {
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).getPassword().equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail() {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        User user = users.get(loggedInUserEmail);

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(user.getEmail()) && user.getPassword().equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            // Ensure the new email is not already taken
            if (!users.containsKey(newEmail)) {
                users.put(newEmail, users.remove(oldEmail));
                System.out.println("Email changed successfully.");
                loggedInUserEmail = newEmail;
            } else {
                System.out.println("New email is already in use.");
            }
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }

    private static void logout() {
        if (loggedInUserEmail != null) {
            System.out.println("Logged out successfully.");
            loggedInUserEmail = null;
        } else {
            System.out.println("You are not logged in.");
        }
    }

    private static class User {
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