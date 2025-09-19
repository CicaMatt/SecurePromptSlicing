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
    
    public boolean validateCredentials(String oldEmail, String password) {
        return this.email.equals(oldEmail) && this.password.equals(password);
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }

    public String getEmail() {
        return email;
    }
}

public class LoginSystem {

    private static Map<String, User> users = new HashMap<>();
    
    static {
        // Sample user
        users.put("john_doe", new User("john_doe", "old_email@example.com", "password123"));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        if (!users.containsKey(username)) {
            System.out.println("User not found.");
            return;
        }
        
        User user = users.get(username);

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (!user.validateCredentials(user.getEmail(), password)) {
            System.out.println("Invalid credentials.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (user.validateCredentials(oldEmail, confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            user.setEmail(newEmail);
            System.out.println("Email updated successfully. New Email: " + user.getEmail());
        } else {
            System.out.println("Old email or password is incorrect.");
        }
    }
}