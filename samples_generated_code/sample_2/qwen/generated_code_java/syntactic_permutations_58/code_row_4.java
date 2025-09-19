import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser = null;

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        system.users.put("user1", new User("user1", "password123", "user1@example.com"));
        Scanner scanner = new Scanner(System.in);
        while (true) {
            if (system.loggedInUser == null) {
                System.out.println("Enter username:");
                String username = scanner.nextLine();
                System.out.println("Enter password:");
                String password = scanner.nextLine();
                system.login(username, password);
            } else {
                System.out.println("Logged in as " + system.loggedInUser.getUsername());
                System.out.println("Enter old email:");
                String oldEmail = scanner.nextLine();
                System.out.println("Enter new email:");
                String newEmail = scanner.nextLine();
                System.out.println("Confirm password:");
                String confirmPassword = scanner.nextLine();
                system.changeEmail(oldEmail, newEmail, confirmPassword);
                system.logout();
            }
        }
    }

    private void login(String username, String password) {
        User user = users.get(username);
        if (user != null && user.getPassword().equals(password)) {
            loggedInUser = user;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    private void logout() {
        loggedInUser = null;
        System.out.println("Logged out.");
    }

    private void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }
        if (!loggedInUser.getEmail().equals(oldEmail)) {
            System.out.println("Incorrect old email.");
            return;
        }
        if (!loggedInUser.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }
        loggedInUser.setEmail(newEmail);
        System.out.println("Email changed successfully to " + newEmail);
    }

    private static class User {
        private String username;
        private String password;
        private String email;

        public User(String username, String password, String email) {
            this.username = username;
            this.password = password;
            this.email = email;
        }

        public String getUsername() {
            return username;
        }

        public String getPassword() {
            return password;
        }

        public void setPassword(String password) {
            this.password = password;
        }

        public String getEmail() {
            return email;
        }

        public void setEmail(String email) {
            this.email = email;
        }
    }
}