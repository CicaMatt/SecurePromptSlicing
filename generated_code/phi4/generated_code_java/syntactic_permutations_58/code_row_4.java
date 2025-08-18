import java.util.Scanner;
import java.util.HashMap;

public class SimpleLoginSystem {

    private static HashMap<String, String> users = new HashMap<>();
    private static String loggedInUserEmail = null;
    private static boolean isLoggedIn = false;

    public static void main(String[] args) {
        // Sample user for demonstration purposes
        users.put("user1@example.com", "password123");

        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("Choose an option: \n1. Login\n2. Change Email\n3. Exit");
            int choice = Integer.parseInt(scanner.nextLine());

            switch (choice) {
                case 1:
                    login(scanner);
                    break;
                case 2:
                    changeEmail(scanner);
                    break;
                case 3:
                    System.out.println("Exiting...");
                    scanner.close();
                    return;
                default:
                    System.out.println("Invalid choice. Please try again.");
            }
        }
    }

    private static void login(Scanner scanner) {
        if (isLoggedIn) {
            System.out.println("You are already logged in.");
            return;
        }

        System.out.print("Enter email: ");
        String email = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUserEmail = email;
            isLoggedIn = true;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid email or password.");
        }
    }

    private static void changeEmail(Scanner scanner) {
        if (!isLoggedIn) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();

        if (loggedInUserEmail.equals(oldEmail) && users.get(loggedInUserEmail).equals(confirmPassword)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            // Update the user's email
            users.remove(loggedInUserEmail);
            users.put(newEmail, confirmPassword);

            loggedInUserEmail = newEmail;
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect old email or password.");
        }
    }
}