import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static HashMap<String, User> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Pre-populate with a sample user
        users.put("user@example.com", new User("user@example.com", "password123"));

        while (true) {
            System.out.println("\n1. Login\n2. Change Email\n3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // consume newline

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    changeEmail();
                    break;
                case 3:
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login() {
        if (loggedInUserEmail != null) {
            System.out.println("Already logged in as " + loggedInUserEmail);
            return;
        }

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);
        if (user != null && user.getPassword().equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail() {
        if (loggedInUserEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        User user = users.get(oldEmail);
        if (user != null && user.getPassword().equals(confirmPassword)) {
            if (!newEmail.equals(oldEmail) && !users.containsKey(newEmail)) {
                users.remove(oldEmail);
                user.setEmail(newEmail);
                users.put(newEmail, user);
                loggedInUserEmail = newEmail;
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email must be different from old email and not already in use.");
            }
        } else {
            System.out.println("Incorrect credentials or new email is already in use.");
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

        public void setEmail(String email) {
            this.email = email;
        }

        public String getPassword() {
            return password;
        }
    }
}