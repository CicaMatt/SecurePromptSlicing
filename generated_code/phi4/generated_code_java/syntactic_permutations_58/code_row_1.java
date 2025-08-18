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
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public LoginSystem() {
        // Initialize with a sample user for demonstration
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUser = users.get(email);
            return true;
        }
        return false;
    }

    public void changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser != null && loggedInUser.getEmail().equals(oldEmail) &&
                loggedInUser.checkPassword(newPassword)) {
            loggedInUser.setEmail(newEmail);
            System.out.println("Email changed successfully to: " + newEmail);
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }

    public void logout() {
        loggedInUser = null;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Logout");
            System.out.println("4. Exit");

            int choice = Integer.parseInt(scanner.nextLine());

            if (choice == 1) {
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                if (loginSystem.login(email, password)) {
                    System.out.println("Login successful");
                } else {
                    System.out.println("Invalid credentials.");
                }
            } else if (choice == 2) {
                if (loginSystem.loggedInUser != null) {
                    System.out.print("Enter old email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("Enter password: ");
                    String newPassword = scanner.nextLine();
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();

                    loginSystem.changeEmail(oldEmail, newPassword, newEmail);
                } else {
                    System.out.println("You must be logged in to change your email.");
                }
            } else if (choice == 3) {
                loginSystem.logout();
                System.out.println("Logged out successfully.");
            } else if (choice == 4) {
                break;
            } else {
                System.out.println("Invalid choice. Please try again.");
            }
        }

        scanner.close();
    }
}