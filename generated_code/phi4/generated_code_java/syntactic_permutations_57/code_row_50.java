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
    
    private static final Map<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Add a default user for demonstration purposes
        users.put("test@example.com", new User("test@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter password: ");
        String confirmPassword = scanner.nextLine();

        if (users.containsKey(oldEmail) && users.get(oldEmail).checkPassword(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (!newEmail.isEmpty() && !newEmail.equals(oldEmail)) { // Ensure the new email is valid and different
                users.put(newEmail, users.remove(oldEmail));
                System.out.println("Email changed successfully to " + newEmail);
            } else {
                System.out.println("Invalid new email.");
            }
        } else {
            System.out.println("Invalid credentials.");
        }

        scanner.close();
    }
}