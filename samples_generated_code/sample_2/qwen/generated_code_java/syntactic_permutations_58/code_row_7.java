import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private Map<String, User> users = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private User loggedInUser = null;

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        system.run();
    }

    public void run() {
        while (true) {
            if (loggedInUser == null) {
                System.out.println("1. Register");
                System.out.println("2. Login");
                System.out.println("3. Exit");
            } else {
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
                System.out.println("3. Exit");
            }
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    if (loggedInUser == null) {
                        register();
                    } else {
                        changeEmail();
                    }
                    break;
                case 2:
                    if (loggedInUser == null) {
                        login();
                    } else {
                        logout();
                    }
                    break;
                case 3:
                    System.exit(0);
            }
        }
    }

    private void register() {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(username)) {
            System.out.println("Username already exists.");
        } else {
            users.put(username, new User(email, password));
            System.out.println("Registration successful.");
        }
    }

    private void login() {
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(username) && users.get(username).checkPassword(password)) {
            loggedInUser = users.get(username);
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid username or password.");
        }
    }

    private void logout() {
        loggedInUser = null;
        System.out.println("Logged out successfully.");
    }

    private void changeEmail() {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (loggedInUser.getEmail().equals(oldEmail) && loggedInUser.checkPassword(password)) {
            loggedInUser.setEmail(newEmail);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid old email or password.");
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

        public void setEmail(String email) {
            this.email = email;
        }

        public boolean checkPassword(String password) {
            return this.password.equals(password);
        }
    }
}