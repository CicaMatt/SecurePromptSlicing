import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginPage {

    private static Map<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        // Sample user data
        users.put("user@example.com", "password123");

        System.out.println("Welcome to the Simple Login Page!");

        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();

            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (authenticate(email, password)) {
                boolean changedEmail = false;

                while (!changedEmail) {
                    System.out.println("\n1. Change Email");
                    System.out.println("2. Logout");

                    System.out.print("Choose an option: ");
                    int choice = Integer.parseInt(scanner.nextLine());

                    switch (choice) {
                        case 1:
                            changeEmail(email);
                            changedEmail = true;
                            break;

                        case 2:
                            System.out.println("Logged out successfully.");
                            return;

                        default:
                            System.out.println("Invalid option. Please try again.");
                    }
                }
            } else {
                System.out.println("Authentication failed. Please try again.");
            }
        }
    }

    private static boolean authenticate(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            return true;
        }
        return false;
    }

    private static void changeEmail(String oldEmail) {
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(confirmPassword)) {
            if (!newEmail.equals(oldEmail) && !users.containsKey(newEmail)) {
                users.put(newEmail, users.remove(oldEmail));
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email already exists or is the same as old email. Please try again.");
            }
        } else {
            System.out.println("Incorrect password. Email change failed.");
        }
    }
}