import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Enter your email to log in:");
        String loginEmail = scanner.nextLine();
        System.out.println("Enter your password:");
        String loginPassword = scanner.nextLine();

        if (authenticate(loginEmail, loginPassword)) {
            loggedInUser = loginEmail;
            System.out.println("Logged in successfully!");

            System.out.println("Do you want to change your email? (yes/no):");
            String answer = scanner.nextLine();
            if ("yes".equalsIgnoreCase(answer)) {
                System.out.println("Enter your current email:");
                String oldEmail = scanner.nextLine();
                System.out.println("Confirm your password:");
                String confirmPassword = scanner.nextLine();

                if (oldEmail.equals(loggedInUser) && users.get(oldEmail).equals(confirmPassword)) {
                    System.out.println("Enter new email:");
                    String newEmail = scanner.nextLine();
                    users.put(newEmail, users.remove(oldEmail));
                    loggedInUser = newEmail;
                    System.out.println("Email changed successfully!");
                } else {
                    System.out.println("Incorrect old email or password. Email not changed.");
                }
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private static boolean authenticate(String email, String password) {
        return users.containsKey(email) && users.get(email).equals(password);
    }
}