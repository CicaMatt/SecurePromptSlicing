import java.util.HashMap;
import java.util.Scanner;

public class LoginSystem {
    private static HashMap<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        while (true) {
            if (loggedInUser == null) {
                System.out.println("Enter your email:");
                String email = scanner.nextLine();
                System.out.println("Enter your password:");
                String password = scanner.nextLine();

                if (users.containsKey(email) && users.get(email).equals(password)) {
                    loggedInUser = email;
                    System.out.println("Logged in successfully.");
                } else {
                    System.out.println("Login failed. Please try again.");
                }
            } else {
                System.out.println("Enter 'change' to update your email or 'logout' to log out:");
                String action = scanner.nextLine();
                if (action.equalsIgnoreCase("change")) {
                    changeEmail(scanner);
                } else if (action.equalsIgnoreCase("logout")) {
                    loggedInUser = null;
                    System.out.println("Logged out successfully.");
                }
            }
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.println("Enter your current email:");
        String oldEmail = scanner.nextLine();
        System.out.println("Confirm your password:");
        String password = scanner.nextLine();
        if (loggedInUser.equals(oldEmail) && users.get(loggedInUser).equals(password)) {
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();
            users.put(newEmail, users.remove(loggedInUser));
            loggedInUser = newEmail;
            System.out.println("Email updated successfully.");
        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }
}