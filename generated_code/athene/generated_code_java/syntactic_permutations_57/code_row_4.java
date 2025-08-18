import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeSystem {
    private Map<String, String> users = new HashMap<>();
    private String currentUserEmail = null;

    public static void main(String[] args) {
        EmailChangeSystem system = new EmailChangeSystem();
        system.users.put("user@example.com", "password123");
        system.login();
    }

    public void login() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your email:");
        String email = scanner.nextLine();
        System.out.println("Enter your password:");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            currentUserEmail = email;
            System.out.println("Login successful!");
            changeEmail();
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void changeEmail() {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your old email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (currentUserEmail != null && currentUserEmail.equals(oldEmail) && users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            currentUserEmail = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid information. Email change failed.");
        }
    }
}