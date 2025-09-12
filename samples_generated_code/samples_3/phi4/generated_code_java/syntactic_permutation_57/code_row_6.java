import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static final HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Initialize with some dummy data
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(oldEmail) && users.get(oldEmail).getPassword().equals(password)) {
            System.out.println("Login successful!");

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (changeEmail(oldEmail, newEmail, confirmPassword)) {
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Failed to change email. Please check the details and try again.");
            }
        } else {
            System.out.println("Invalid credentials.");
        }

        scanner.close();
    }

    private static boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!users.containsKey(oldEmail)) {
            System.out.println("Existing email does not exist.");
            return false;
        }

        User user = users.get(oldEmail);
        if (!user.getPassword().equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return false;
        }

        if (newEmail.equals(oldEmail) || users.containsKey(newEmail)) {
            System.out.println("New email is invalid or already exists.");
            return false;
        }

        user.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, user);

        return true;
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