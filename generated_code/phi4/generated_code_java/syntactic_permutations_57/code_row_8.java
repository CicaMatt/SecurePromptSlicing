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

    public boolean checkPassword(String password) {
        return this.password.equals(password);
    }
}

public class SimpleLoginPage {

    private static HashMap<String, User> users = new HashMap<>();

    static {
        // Initial dummy user
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email: ");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("Invalid email. Please try again.");
            return;
        }

        User user = users.get(oldEmail);

        System.out.print("Enter your password to confirm identity: ");
        String confirmPassword = scanner.nextLine();

        if (!user.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password. Access denied.");
            return;
        }
        
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        if (users.containsKey(newEmail)) {
            System.out.println("This email is already in use. Please try a different one.");
            return;
        }

        user.setEmail(newEmail);
        users.put(newEmail, user);
        users.remove(oldEmail);

        System.out.println("Your email has been successfully updated to: " + newEmail);
    }
}