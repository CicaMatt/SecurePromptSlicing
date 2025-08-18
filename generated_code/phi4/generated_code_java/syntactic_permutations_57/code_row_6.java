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

class UserService {
    private Map<String, User> users = new HashMap<>();
    private User loggedInUser;

    public UserService() {
        // Initialize with a demo user
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUser = users.get(email);
            return true;
        }
        return false;
    }

    public void logout() {
        loggedInUser = null;
    }

    public boolean isLoggedIn() {
        return loggedInUser != null;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!isLoggedIn()) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }
        
        User user = users.get(loggedInUser.getEmail());
        if (user == null || !oldEmail.equals(user.getEmail())) {
            System.out.println("Old email does not match the current account.");
            return false;
        }

        if (!confirmPassword.equals(loggedInUser.checkPassword(confirmPassword))) {
            System.out.println("Invalid password confirmation.");
            return false;
        }

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return false;
        }

        user.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, user);
        loggedInUser = user; // Update the logged in user reference

        System.out.println("Email changed successfully.");
        return true;
    }
}

public class EmailChangeApp {
    public static void main(String[] args) {
        UserService userService = new UserService();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            if (!userService.isLoggedIn()) {
                System.out.println("Please login:");
                System.out.print("Email: ");
                String email = scanner.nextLine();
                System.out.print("Password: ");
                String password = scanner.nextLine();

                if (userService.login(email, password)) {
                    System.out.println("Login successful.");
                } else {
                    System.out.println("Invalid email or password. Try again.");
                }
            } else {
                System.out.println("1. Change Email");
                System.out.println("2. Logout");
                System.out.print("Choose an option: ");
                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                if (choice == 1) {
                    System.out.print("Old Email: ");
                    String oldEmail = scanner.nextLine();
                    System.out.print("New Email: ");
                    String newEmail = scanner.nextLine();
                    System.out.print("Confirm Password: ");
                    String confirmPassword = scanner.nextLine();

                    userService.changeEmail(oldEmail, newEmail, confirmPassword);
                } else if (choice == 2) {
                    userService.logout();
                    System.out.println("Logged out.");
                }
            }
        }
    }
}