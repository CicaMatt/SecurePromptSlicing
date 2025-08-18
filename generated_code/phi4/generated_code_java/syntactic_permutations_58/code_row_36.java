import java.util.HashMap;
import java.util.Map;
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
    private Map<String, User> users;
    private User loggedInUser;

    public LoginSystem() {
        users = new HashMap<>();
        // Sample user
        users.put("user1", new User("user1", "old@example.com", "password123"));
    }

    public boolean login(String username, String password) {
        User user = users.get(username);
        if (user != null && user.checkPassword(password)) {
            loggedInUser = user;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return false;
        }
        if (!loggedInUser.getEmail().equals(oldEmail)) {
            System.out.println("Old email does not match our records.");
            return false;
        }
        if (!loggedInUser.checkPassword(newPassword)) {
            System.out.println("Incorrect password.");
            return false;
        }
        loggedInUser.setEmail(newEmail);
        System.out.println("Email updated successfully to " + newEmail);
        return true;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Username: ");
        String username = scanner.nextLine();

        System.out.print("Password: ");
        String password = scanner.nextLine();

        if (system.login(username, password)) {
            System.out.println("Login successful!");

            System.out.print("Old email: ");
            String oldEmail = scanner.nextLine();

            System.out.print("New email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Password to confirm change: ");
            String newPassword = scanner.nextLine();

            system.changeEmail(oldEmail, newPassword, newEmail);
        } else {
            System.out.println("Login failed. Please check your username and password.");
        }

        scanner.close();
    }
}