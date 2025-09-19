import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class User {
    private String email;
    private String password; // Assume passwords are stored securely in practice

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

    public boolean checkPassword(String confirmPassword) {
        return this.password.equals(confirmPassword);
    }
}

public class SimpleLoginSystem {

    private static Map<String, User> users = new HashMap<>();

    static {
        // Prepopulate with a sample user
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email: ");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("No such user found. Exiting.");
            return;
        }
        
        User loggedInUser = users.get(oldEmail);
        
        System.out.print("Enter confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!loggedInUser.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password. Exiting.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        if (users.containsKey(newEmail)) {
            System.out.println("New email already exists. Try again with a different email.");
            return;
        }
        
        loggedInUser.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, loggedInUser);

        System.out.println("Email updated successfully!");
    }
}