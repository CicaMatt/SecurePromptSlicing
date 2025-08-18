import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Enter your email to log in:");
        String loginEmail = scanner.nextLine();
        System.out.println("Enter your password to log in:");
        String loginPassword = scanner.nextLine();

        if (users.containsKey(loginEmail) && users.get(loginEmail).equals(loginPassword)) {
            loggedInUser = loginEmail;
            System.out.println("Logged in successfully.");

            System.out.println("Would you like to change your email? (yes/no):");
            String answer = scanner.nextLine();
            if ("yes".equalsIgnoreCase(answer)) {
                changeEmail(scanner);
            } else {
                System.out.println("No changes made.");
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.println("Enter current email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(loggedInUser) && users.get(oldEmail).equals(confirmPassword)) {
            System.out.println("Enter new email:");
            String newEmail = scanner.nextLine();
            users.put(newEmail, users.remove(oldEmail));
            loggedInUser = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect current email or password. Email not changed.");
        }
    }
}