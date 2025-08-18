import java.util.HashMap;
import java.util.Scanner;

class User {
    String email;
    String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }
}

public class EmailChangeApp {

    private static HashMap<String, User> userDatabase = new HashMap<>();

    public static void main(String[] args) {
        // Predefined users
        userDatabase.put("user1@example.com", new User("user1@example.com", "password123"));
        userDatabase.put("user2@example.com", new User("user2@example.com", "pass456"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        if (!userDatabase.containsKey(oldEmail)) {
            System.out.println("Old email does not exist.");
            return;
        }

        User user = userDatabase.get(oldEmail);

        System.out.println("Enter confirm password:");
        String confirmPassword = scanner.nextLine();
        
        if (!confirmPassword.equals(user.password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        if (newEmail.isEmpty() || !newEmail.contains("@")) {
            System.out.println("Invalid new email format.");
            return;
        }
        
        if (userDatabase.containsKey(newEmail)) {
            System.out.println("New email already exists.");
            return;
        }

        user.email = newEmail;
        userDatabase.remove(oldEmail);
        userDatabase.put(newEmail, user);

        System.out.println("Email changed successfully to: " + newEmail);
    }
}