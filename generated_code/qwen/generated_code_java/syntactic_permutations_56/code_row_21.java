import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private static final Map<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample user data
        users.put("user1", new User("user1", "password123", "user1@example.com"));

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username:");
        String username = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (authenticate(username, password)) {
            changeEmail(scanner, username);
        } else {
            System.out.println("Authentication failed. Please try again.");
        }

        scanner.close();
    }

    private static boolean authenticate(String username, String password) {
        User user = users.get(username);
        return user != null && user.getPassword().equals(password);
    }

    private static void changeEmail(Scanner scanner, String username) {
        System.out.println("Enter old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();
        System.out.println("Confirm new email:");
        String confirmEmail = scanner.nextLine();
        System.out.println("Enter password to confirm changes:");
        String password = scanner.nextLine();

        User user = users.get(username);
        if (!user.getEmail().equals(oldEmail)) {
            System.out.println("Old email does not match. Please try again.");
        } else if (!newEmail.equals(confirmEmail)) {
            System.out.println("New email and confirmation do not match. Please try again.");
        } else if (oldEmail.equals(newEmail)) {
            System.out.println("New email must be different from the old email. Please try again.");
        } else if (!authenticate(username, password)) {
            System.out.println("Incorrect password. Please try again.");
        } else {
            user.setEmail(newEmail);
            System.out.println("Email changed successfully.");
        }
    }

    static class User {
        private String username;
        private String password;
        private String email;

        public User(String username, String password, String email) {
            this.username = username;
            this.password = password;
            this.email = email;
        }

        public String getPassword() {
            return password;
        }

        public String getEmail() {
            return email;
        }

        public void setEmail(String email) {
            this.email = email;
        }
    }
}