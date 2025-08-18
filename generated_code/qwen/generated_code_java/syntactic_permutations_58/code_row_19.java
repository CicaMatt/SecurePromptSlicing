import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private boolean isLoggedIn = false;
    private Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        system.userCredentials.put("user@example.com", "password123");
        system.run();
    }

    public void run() {
        System.out.println("Welcome to the Simple Login System.");
        login();
        if (isLoggedIn) {
            changeEmail();
        }
    }

    private void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            isLoggedIn = true;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password. Login failed.");
        }
    }

    private void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String password = scanner.nextLine();

        if (userCredentials.containsKey(oldEmail) && userCredentials.get(oldEmail).equals(password)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, password);
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Invalid old email or password. Email change failed.");
        }
    }
}