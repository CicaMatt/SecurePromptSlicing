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

    public boolean verifyPassword(String password) {
        return this.password.equals(password);
    }
}

class UserManager {
    private HashMap<String, User> users = new HashMap<>();

    public UserManager() {
        // Sample users
        users.put("user1@example.com", new User("user1@example.com", "password123"));
    }

    public boolean isUserLoggedIn(String email) {
        return users.containsKey(email);
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (!users.containsKey(oldEmail)) {
            return false;
        }
        
        User user = users.get(oldEmail);
        if (user.verifyPassword(newPassword)) {
            users.remove(oldEmail);
            user.setEmail(newEmail);
            users.put(newEmail, user);
            return true;
        }

        return false;
    }
}

public class SimpleLoginApp {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        UserManager userManager = new UserManager();

        System.out.println("Enter your email:");
        String oldEmail = scanner.nextLine();
        
        if (!userManager.isUserLoggedIn(oldEmail)) {
            System.out.println("User not logged in or does not exist.");
            return;
        }

        System.out.println("Enter your password:");
        String confirmPassword = scanner.nextLine();

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        boolean success = userManager.changeEmail(oldEmail, confirmPassword, newEmail);

        if (success) {
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Failed to change email. Please check your information.");
        }
    }
}