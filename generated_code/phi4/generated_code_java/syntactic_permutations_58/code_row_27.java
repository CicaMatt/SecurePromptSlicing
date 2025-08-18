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

class LoginSystem {
    private Map<String, User> users;
    private String loggedInUserEmail;

    public LoginSystem() {
        users = new HashMap<>();
        users.put("user@example.com", new User("user@example.com", "password123"));
        loggedInUserEmail = null;
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email)) {
            User user = users.get(email);
            if (user.checkPassword(password)) {
                loggedInUserEmail = email;
                System.out.println("Login successful!");
                return true;
            }
        }
        System.out.println("Invalid credentials.");
        return false;
    }

    public boolean isLoggedIn() {
        return loggedInUserEmail != null;
    }

    public void logout() {
        loggedInUserEmail = null;
        System.out.println("Logged out successfully.");
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (!isLoggedIn()) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }

        User user = users.get(loggedInUserEmail);
        if (user.getEmail().equals(oldEmail) && user.checkPassword(newPassword)) {
            user.setEmail(newEmail);
            System.out.println("Email changed successfully!");
            return true;
        } else {
            System.out.println("Invalid old email or password.");
            return false;
        }
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            if (!loginSystem.isLoggedIn()) {
                System.out.print("Enter your email: ");
                String email = scanner.nextLine();
                System.out.print("Enter your password: ");
                String password = scanner.nextLine();

                loginSystem.login(email, password);
            } else {
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
                System.out.print("Choose an option: ");
                int choice = Integer.parseInt(scanner.nextLine());

                if (choice == 1) {
                    System.out.print("Enter your old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Confirm your password: ");
                    String newPassword = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();

                    loginSystem.changeEmail(oldEmail, newPassword, newEmail);
                } else if (choice == 2) {
                    loginSystem.logout();
                }
            }

            System.out.println(); // Add a blank line for better readability.
        }
    }
}