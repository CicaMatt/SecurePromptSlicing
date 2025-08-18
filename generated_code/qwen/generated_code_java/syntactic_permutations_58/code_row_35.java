import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private Map<String, String> userCredentials = new HashMap<>();
    private String loggedInUserEmail;

    public static void main(String[] args) {
        SimpleLoginSystem system = new SimpleLoginSystem();
        system.userCredentials.put("user@example.com", "password123");
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter email:");
        String email = scanner.nextLine();
        System.out.println("Enter password:");
        String password = scanner.nextLine();

        if (system.login(email, password)) {
            System.out.println("Login successful. Change email?");
            if (scanner.next().equalsIgnoreCase("yes")) {
                System.out.println("Enter old email:");
                String oldEmail = scanner.next();
                System.out.println("Confirm password:");
                String confirmPassword = scanner.next();
                System.out.println("Enter new email:");
                String newEmail = scanner.next();

                if (system.changeEmail(oldEmail, confirmPassword, newEmail)) {
                    System.out.println("Email changed successfully.");
                } else {
                    System.out.println("Failed to change email. Incorrect old email or password.");
                }
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private boolean login(String email, String password) {
        if (userCredentials.containsKey(email) && userCredentials.get(email).equals(password)) {
            loggedInUserEmail = email;
            return true;
        }
        return false;
    }

    private boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (loggedInUserEmail != null && loggedInUserEmail.equals(oldEmail) &&
                userCredentials.containsKey(loggedInUserEmail) &&
                userCredentials.get(loggedInUserEmail).equals(confirmPassword)) {

            userCredentials.remove(loggedInUserEmail);
            userCredentials.put(newEmail, confirmPassword);
            loggedInUserEmail = newEmail;
            return true;
        }
        return false;
    }
}