import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private Scanner scanner = new Scanner(System.in);
    private String loggedInUserEmail;

    public SimpleLoginSystem() {
        // Adding a default user for demonstration purposes
        userCredentials.put("user@example.com", "password123");
    }

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        system.run();
    }

    private void run() {
        System.out.println("Welcome to the Simple Login System!");
        while (true) {
            if (loggedInUserEmail == null) {
                login();
            } else {
                changeEmail();
            }
        }
    }

    private void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            System.out.println("Login successful!");
        } else {
            System.out.println("Invalid email or password. Please try again.");
        }
    }

    private void changeEmail() {
        System.out.print("Enter your current email: ");
        String currentEmail = scanner.nextLine();
        System.out.print("Enter your password to confirm: ");
        String password = scanner.nextLine();

        if (currentEmail.equals(loggedInUserEmail) && userCredentials.containsKey(currentEmail) && userCredentials.get(currentEmail).equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            userCredentials.remove(currentEmail);
            userCredentials.put(newEmail, password);
            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully!");
        } else {
            System.out.println("Invalid current email or password. Email change failed.");
        }

        // Logout after changing email
        loggedInUserEmail = null;
    }
}