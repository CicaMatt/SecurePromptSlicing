import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> users; // Maps email to password

    public SimpleLoginSystem() {
        this.users = new HashMap<>();
        // Adding a sample user for demonstration purposes
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }

    public void changeEmail(String oldEmail, String newEmail, String password) {
        if (login(oldEmail, password)) {
            users.remove(oldEmail);
            users.put(newEmail, password);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect email or password. Email not changed.");
        }
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();

        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();

        system.changeEmail(oldEmail, newEmail, password);
    }
}