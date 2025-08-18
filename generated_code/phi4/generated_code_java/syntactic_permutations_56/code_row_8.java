import java.util.HashMap;
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

public class SimpleLoginSystem {

    private static final HashMap<String, User> usersDatabase = new HashMap<>();

    static {
        // Dummy users for demonstration
        usersDatabase.put("user1", new User("user1", "user1@example.com", "password123"));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter username:");
        String username = scanner.nextLine();

        if (!usersDatabase.containsKey(username)) {
            System.out.println("User not found.");
            return;
        }

        User user = usersDatabase.get(username);

        System.out.println("Enter password:");
        String enteredPassword = scanner.nextLine();
        
        if (!user.checkPassword(enteredPassword)) {
            System.out.println("Incorrect password. Access denied.");
            return;
        }
        
        boolean emailChanged = false;

        while (!emailChanged) {
            System.out.println("Enter old email:");
            String oldEmail = scanner.nextLine();

            if (!oldEmail.equals(user.getEmail())) {
                System.out.println("Old email does not match the current email. Try again.");
                continue;
            }

            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();

            if (newEmail.equals(oldEmail)) {
                System.out.println("New email must be different from the old email. Try again.");
                continue;
            }
            
            System.out.println("Confirm password:");
            String confirmPassword = scanner.nextLine();
            
            if (!enteredPassword.equals(confirmPassword)) {
                System.out.println("Passwords do not match. Try again.");
                continue;
            }

            user.setEmail(newEmail);
            emailChanged = true;
            System.out.println("Email changed successfully!");
        }
        
        scanner.close();
    }
}