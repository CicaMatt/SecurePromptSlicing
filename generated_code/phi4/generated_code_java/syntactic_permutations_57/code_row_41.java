import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample data for testing
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your email:");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("User not found.");
            return;
        }

        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        User user = users.get(oldEmail);
        
        if (!user.getPassword().equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        users.remove(oldEmail);
        User newUser = new User(newEmail, password);
        users.put(newEmail, newUser);

        System.out.println("Email changed successfully to: " + newEmail);
    }
}

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

    public String getPassword() {
        return password;
    }
}