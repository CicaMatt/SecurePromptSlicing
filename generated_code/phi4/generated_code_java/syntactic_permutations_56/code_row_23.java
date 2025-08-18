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

    private static HashMap<String, User> usersDatabase = new HashMap<>();
    private static String currentUserEmail;

    public static void main(String[] args) {
        // Sample user for demonstration
        usersDatabase.put("user@example.com", new User("user@example.com", "password123"));

        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter email:");
        String email = scanner.nextLine();

        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (login(email, password)) {
            System.out.println("Login successful!");
            changeEmail(scanner);
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static boolean login(String email, String password) {
        User user = usersDatabase.get(email);
        if (user != null && user.checkPassword(password)) {
            currentUserEmail = email;
            return true;
        }
        return false;
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter old email:");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(currentUserEmail)) {
            System.out.println("Old email does not match current session email.");
            return;
        }

        System.out.println("Enter new email:");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from old email.");
            return;
        }

        System.out.println("Confirm password:");
        String confirmPassword = scanner.nextLine();

        User user = usersDatabase.get(currentUserEmail);
        if (!user.checkPassword(confirmPassword)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }

        usersDatabase.remove(oldEmail);
        user.setEmail(newEmail);
        usersDatabase.put(newEmail, user);

        currentUserEmail = newEmail;

        System.out.println("Email changed successfully to " + newEmail);
    }
}