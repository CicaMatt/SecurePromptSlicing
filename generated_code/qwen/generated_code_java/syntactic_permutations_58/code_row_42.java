import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.initializeUsers();
        system.run();
    }

    private void initializeUsers() {
        users.put("user1", new User("user1", "password1", "user1@example.com"));
    }

    private void run() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter username:");
        String username = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (login(username, password)) {
            System.out.println("Login successful. Would you like to change your email? (yes/no)");
            String response = scanner.nextLine();
            if ("yes".equalsIgnoreCase(response)) {
                System.out.println("Enter old email:");
                String oldEmail = scanner.nextLine();
                System.out.println("Confirm password:");
                String confirmPassword = scanner.nextLine();

                if (changeEmail(oldEmail, confirmPassword)) {
                    System.out.println("Email changed successfully.");
                } else {
                    System.out.println("Failed to change email. Incorrect old email or password.");
                }
            }
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }
    }

    private boolean login(String username, String password) {
        User user = users.get(username);
        if (user != null && user.getPassword().equals(password)) {
            loggedInUser = user;
            return true;
        }
        return false;
    }

    private boolean changeEmail(String oldEmail, String confirmPassword) {
        if (loggedInUser != null && loggedInUser.getEmail().equals(oldEmail) && loggedInUser.getPassword().equals(confirmPassword)) {
            System.out.println("Enter new email:");
            Scanner scanner = new Scanner(System.in);
            String newEmail = scanner.nextLine();
            loggedInUser.setEmail(newEmail);
            return true;
        }
        return false;
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