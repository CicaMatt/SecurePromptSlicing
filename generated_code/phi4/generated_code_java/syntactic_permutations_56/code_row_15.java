import java.util.HashMap;
import java.util.Scanner;

class LoginSystem {
    private HashMap<String, String> users = new HashMap<>();
    
    public void registerUser(String email, String password) {
        if (!users.containsKey(email)) {
            users.put(email, password);
        }
    }
    
    public boolean loginUser(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword, String currentPassword) {
        if (!loginUser(oldEmail, currentPassword)) {
            System.out.println("Incorrect password.");
            return false;
        }
        
        if (oldEmail.equals(newEmail)) {
            System.out.println("New email must be different from the old one.");
            return false;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);

        System.out.println("Email changed successfully!");
        return true;
    }

    public static void main(String[] args) {
        LoginSystem system = new LoginSystem();
        
        // Register a user for demo
        system.registerUser("user@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        System.out.println("Enter your password:");
        String currentPassword = scanner.nextLine();
        
        if (system.loginUser(oldEmail, currentPassword)) {
            System.out.println("Login successful. You can now change your email.");
            
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            System.out.println("Confirm your new password:");
            String confirmPassword = scanner.nextLine();

            system.changeEmail(oldEmail, newEmail, confirmPassword, currentPassword);
        } else {
            System.out.println("Login failed. Please check your credentials.");
        }

        scanner.close();
    }
}