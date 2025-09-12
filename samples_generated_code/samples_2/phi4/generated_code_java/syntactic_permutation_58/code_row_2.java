import java.util.HashMap;
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
    private HashMap<String, User> users = new HashMap<>();
    private User loggedInUser = null;

    public void registerUser(String email, String password) {
        if (!users.containsKey(email)) {
            users.put(email, new User(email, password));
        } else {
            System.out.println("Email already registered.");
        }
    }

    public boolean loginUser(String email, String password) {
        if (users.containsKey(email) && users.get(email).checkPassword(password)) {
            loggedInUser = users.get(email);
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (loggedInUser != null && loggedInUser.getEmail().equals(oldEmail) 
                && loggedInUser.checkPassword(newPassword)) {
            if (!users.containsKey(newEmail)) {
                users.remove(loggedInUser.getEmail());
                loggedInUser.setEmail(newEmail);
                users.put(newEmail, loggedInUser);
                System.out.println("Email changed successfully.");
                return true;
            } else {
                System.out.println("New email already in use.");
            }
        } else {
            System.out.println("Invalid old email or password.");
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        LoginSystem loginSystem = new LoginSystem();

        // Register a user for testing
        loginSystem.registerUser("user@example.com", "password123");

        System.out.println("Enter email to log in:");
        String email = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (loginSystem.loginUser(email, password)) {
            System.out.println("Login successful!");
            boolean changed = false;
            while (!changed) {
                System.out.println("Enter old email to change it:");
                String oldEmail = scanner.nextLine();
                System.out.println("Enter current password:");
                String currPassword = scanner.nextLine();
                System.out.println("Enter new email:");
                String newEmail = scanner.nextLine();

                changed = loginSystem.changeEmail(oldEmail, currPassword, newEmail);
            }
        } else {
            System.out.println("Login failed.");
        }

        scanner.close();
    }
}