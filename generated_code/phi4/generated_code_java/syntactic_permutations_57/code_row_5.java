import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginPage {

    private static HashMap<String, User> users = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        // Sample user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
            String choice = scanner.nextLine();

            switch (choice) {
                case "1":
                    login(scanner);
                    break;
                case "2":
                    if (loggedInUserEmail != null) {
                        changeEmail(scanner);
                    } else {
                        System.out.println("You must be logged in to change your email.");
                    }
                    break;
                case "3":
                    System.exit(0);
                    break;
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

        User user = users.get(email);
        if (user != null && user.getPassword().equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the logged in user.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        User user = users.get(oldEmail);
        if (user != null && user.getPassword().equals(confirmPassword)) {
            users.remove(oldEmail);
            user.setEmail(newEmail);
            users.put(newEmail, user);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Incorrect password.");
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