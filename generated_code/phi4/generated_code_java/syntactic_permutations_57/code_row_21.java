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

    private static Map<String, User> users = new HashMap<>();

    // Initialize with a sample user for demonstration purposes.
    static {
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        
        if (!users.containsKey(oldEmail)) {
            System.out.println("The provided email does not exist.");
            return;
        }

        User user = users.get(oldEmail);

        System.out.print("Enter your password to confirm identity: ");
        String confirmPassword = scanner.nextLine();

        if (!user.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        
        if (users.containsKey(newEmail)) {
            System.out.println("The new email is already in use.");
            return;
        }

        user.setEmail(newEmail);
        users.put(newEmail, user);
        users.remove(oldEmail);

        System.out.println("Email successfully changed to: " + newEmail);
    }
}