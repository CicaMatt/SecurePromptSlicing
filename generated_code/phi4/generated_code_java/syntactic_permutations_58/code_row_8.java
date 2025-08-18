import java.util.HashMap;
import java.util.Scanner;

class User {
    private String username;
    private String email;
    private String password;

    public User(String username, String email, String password) {
        this.username = username;
        this.email = email;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public String getEmail() {
        return email;
    }

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }
}

class LoginSystem {
    private HashMap<String, User> users = new HashMap<>();
    private User loggedInUser;

    public void signUp(String username, String email, String password) {
        if (!users.containsKey(username)) {
            users.put(username, new User(username, email, password));
        } else {
            System.out.println("Username already exists.");
        }
    }

    public boolean login(String username, String password) {
        if (users.containsKey(username)) {
            User user = users.get(username);
            if (user.checkPassword(password)) {
                loggedInUser = user;
                return true;
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Username does not exist.");
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser != null && loggedInUser.getEmail().equals(oldEmail)
                && loggedInUser.checkPassword(newPassword)) {
            loggedInUser.setEmail(newEmail);
            System.out.println("Email updated successfully.");
            return true;
        } else {
            System.out.println("Old email or password is incorrect.");
            return false;
        }
    }

    public void logout() {
        loggedInUser = null;
    }
}

public class Main {
    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        loginSystem.signUp("john_doe", "old_email@example.com", "password123");

        System.out.println("Enter username:");
        String username = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (loginSystem.login(username, password)) {
            System.out.println("Login successful.");
            
            System.out.println("Enter old email:");
            String oldEmail = scanner.nextLine();
            
            System.out.println("Confirm your password:");
            String newPassword = scanner.nextLine();
            
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            loginSystem.changeEmail(oldEmail, newPassword, newEmail);
        }

        loginSystem.logout();
    }
}