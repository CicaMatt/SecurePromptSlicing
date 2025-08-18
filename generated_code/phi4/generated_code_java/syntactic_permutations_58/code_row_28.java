import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static final Map<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        // Sample user for demonstration purposes
        users.put("user1@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        boolean loggedIn = false;
        String currentEmail = null;

        while (true) {
            if (!loggedIn) {
                System.out.println("Login:");
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                if (users.containsKey(email) && users.get(email).equals(password)) {
                    loggedIn = true;
                    currentEmail = email;
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid email or password.");
                }
            } else {
                System.out.println("\nChange Email:");
                System.out.print("Enter old email: ");
                String oldEmail = scanner.nextLine();
                if (!oldEmail.equals(currentEmail)) {
                    System.out.println("Old email does not match the logged-in email.");
                    continue;
                }

                System.out.print("Confirm password: ");
                String confirmPassword = scanner.nextLine();

                if (users.get(oldEmail).equals(confirmPassword)) {
                    System.out.print("Enter new email: ");
                    String newEmail = scanner.nextLine();
                    users.put(newEmail, users.remove(oldEmail));
                    currentEmail = newEmail;
                    System.out.println("Email changed successfully.");
                } else {
                    System.out.println("Incorrect password. Email not changed.");
                }

                loggedIn = false; // Logout after changing email
            }
        }
    }
}