import java.util.HashMap;
import java.util.Scanner;

public class EmailChangeSystem {
    private static final HashMap<String, User> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample user for demonstration purposes
        users.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your email: ");
        String oldEmail = scanner.nextLine();

        if (!users.containsKey(oldEmail)) {
            System.out.println("User not found.");
            return;
        }

        User user = users.get(oldEmail);
        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        if (!enteredPassword.equals(user.getPassword())) {
            System.out.println("Incorrect password.");
            return;
        }

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        user.setEmail(newEmail);
        users.remove(oldEmail);
        users.put(newEmail, user);

        System.out.println("Email changed successfully to " + newEmail);
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