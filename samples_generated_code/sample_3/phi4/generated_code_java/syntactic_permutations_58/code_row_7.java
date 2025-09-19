import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static HashMap<String, User> users = new HashMap<>();
    private static String loggedInEmail = null;

    public static void main(String[] args) {
        // Initial setup with a user for demonstration purposes.
        users.put("user1@example.com", new User("user1@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Choose an option:");
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");

            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid option. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (loggedInEmail != null) {
            System.out.println("Already logged in as " + loggedInEmail);
            return;
        }

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        User user = users.get(email);

        if (user != null && user.getPassword().equals(password)) {
            loggedInEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInEmail == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        User user = users.get(loggedInEmail);

        if (user != null && user.getPassword().equals(confirmPassword) && loggedInEmail.equals(oldEmail)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            
            // Ensure the new email is not already in use.
            if (!users.containsKey(newEmail)) {
                users.remove(loggedInEmail);
                user.setEmail(newEmail);
                users.put(newEmail, user);
                loggedInEmail = newEmail;
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("The new email is already in use. Please try again.");
            }
        } else {
            System.out.println("Invalid old email or password. Email not changed.");
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