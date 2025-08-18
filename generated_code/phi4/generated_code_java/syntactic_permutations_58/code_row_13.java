import java.util.HashMap;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static HashMap<String, String> users = new HashMap<>();

    public static void main(String[] args) {
        // Initial setup for demonstration purposes
        users.put("user1@example.com", "password123");

        Scanner scanner = new Scanner(System.in);
        boolean isLoggedIn = false;
        String loggedInEmail = "";

        while (true) {
            if (!isLoggedIn) {
                System.out.println("Please log in to continue:");
                System.out.print("Enter email: ");
                String email = scanner.nextLine();
                System.out.print("Enter password: ");
                String password = scanner.nextLine();

                if (users.containsKey(email) && users.get(email).equals(password)) {
                    isLoggedIn = true;
                    loggedInEmail = email;
                    System.out.println("Login successful!");
                } else {
                    System.out.println("Invalid email or password.");
                }
            }

            if (isLoggedIn) {
                System.out.println("You are logged in as: " + loggedInEmail);
                System.out.println("Choose an option:");
                System.out.println("1. Change email");
                System.out.println("2. Logout");

                int choice = scanner.nextInt();
                scanner.nextLine(); // Consume newline

                switch (choice) {
                    case 1:
                        changeEmail(scanner, loggedInEmail);
                        break;
                    case 2:
                        isLoggedIn = false;
                        loggedInEmail = "";
                        System.out.println("Logged out successfully.");
                        break;
                    default:
                        System.out.println("Invalid option. Please try again.");
                }
            }
        }
    }

    private static void changeEmail(Scanner scanner, String currentEmail) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(currentEmail) && users.get(oldEmail).equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (!users.containsKey(newEmail)) {
                users.remove(oldEmail);
                users.put(newEmail, users.get(oldEmail));
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("New email is already in use.");
            }
        } else {
            System.out.println("Old email or password is incorrect. Email not changed.");
        }
    }
}