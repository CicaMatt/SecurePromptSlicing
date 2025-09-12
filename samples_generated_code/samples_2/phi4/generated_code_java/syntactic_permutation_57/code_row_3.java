import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Initialize some dummy users for testing purposes
        users.put("user1@example.com", new User("user1@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Please enter your email:");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("Invalid email. Try again.");
            return;
        }

        System.out.println("Enter password for verification:");
        String confirmPassword = scanner.nextLine();
        
        User user = users.get(oldEmail);
        if (!user.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect password. Access denied.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        if (users.containsKey(newEmail) || newEmail.isEmpty()) {
            System.out.println("Invalid new email. Try again.");
            return;
        }

        user.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, user);

        System.out.println("Email successfully updated to: " + newEmail);
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

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }
}