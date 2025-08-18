import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginSystem {
    private static Map<String, String> userCredentials = new HashMap<>();
    private static String loggedInUserEmail = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Adding a default user for demonstration purposes
        userCredentials.put("user@example.com", "password123");

        System.out.println("Login System");
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (login(email, password)) {
            System.out.println("Logged in successfully.");
            System.out.print("Do you want to change your email? (yes/no): ");
            String changeEmailResponse = scanner.nextLine();

            if ("yes".equalsIgnoreCase(changeEmailResponse)) {
                System.out.print("Enter your old email: ");
                String oldEmail = scanner.nextLine();
                System.out.print("Confirm your password: ");
                String confirmPassword = scanner.nextLine();
                System.out.print("Enter new email: ");
                String newEmail = scanner.nextLine();

                if (changeEmail(oldEmail, confirmPassword, newEmail)) {
                    System.out.println("Email changed successfully.");
                } else {
                    System.out.println("Failed to change email. Please check your old email and password.");
                }
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private static boolean login(String email, String password) {
        return userCredentials.containsKey(email) && userCredentials.get(email).equals(password);
    }

    private static boolean changeEmail(String oldEmail, String confirmPassword, String newEmail) {
        if (login(loggedInUserEmail, confirmPassword) && loggedInUserEmail.equals(oldEmail)) {
            userCredentials.remove(oldEmail);
            userCredentials.put(newEmail, confirmPassword);
            loggedInUserEmail = newEmail;
            return true;
        }
        return false;
    }
}