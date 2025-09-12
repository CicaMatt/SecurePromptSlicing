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

public class SimpleLoginPage {

    private static final Map<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample users
        users.put("user1@example.com", new User("user1@example.com", "password123"));
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("Invalid email. Please try again.");
            return;
        }
        
        System.out.println("Confirm Password:");
        String confirmPassword = scanner.nextLine();
        
        User user = users.get(oldEmail);
        if (!user.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }
        
        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists. Please try again.");
            return;
        }

        user.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, user);

        System.out.println("Email changed successfully to: " + newEmail);
    }
}