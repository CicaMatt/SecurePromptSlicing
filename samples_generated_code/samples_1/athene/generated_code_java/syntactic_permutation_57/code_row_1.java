import java.util.HashMap;
import java.util.Scanner;

public class LoginPage {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");

        while (true) {
            System.out.println("1. Login\n2. Change Email\n3. Exit");
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
                    System.exit(0);
                    break;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Logged in successfully.");
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void changeEmail() {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (loggedInUser.equals(oldEmail) && users.get(oldEmail).equals(confirmPassword)) {
            users.remove(oldEmail);
            users.put(newEmail, confirmPassword);
            loggedInUser = newEmail;
            System.out.println("Your email has been changed successfully.");
        } else {
            System.out.println("Invalid information. Please try again.");
        }
    }
}