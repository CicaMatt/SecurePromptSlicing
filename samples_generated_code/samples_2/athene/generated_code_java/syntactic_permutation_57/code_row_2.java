import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeLogin {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static boolean isLoggedIn = false;
    private static String loggedInUser = "";

    public static void main(String[] args) {
        users.put("user@example.com", "password123");
        displayMenu();
    }

    private static void displayMenu() {
        while (true) {
            System.out.println("1. Login");
            System.out.println("2. Change Email");
            System.out.println("3. Exit");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    login();
                    break;
                case 2:
                    changeEmail();
                    break;
                case 3:
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login() {
        if (isLoggedIn) {
            System.out.println("You are already logged in.");
            return;
        }

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
            loggedInUser = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    private static void changeEmail() {
        if (!isLoggedIn) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (!loggedInUser.equals(oldEmail) || !users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect old email or confirm password.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;

        System.out.println("Email changed successfully.");
    }
}