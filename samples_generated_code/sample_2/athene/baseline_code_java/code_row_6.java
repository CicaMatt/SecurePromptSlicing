import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeApp {
    private static final Map<String, String> users = new HashMap<>();
    private static String currentUser;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Please log in to continue.");
        login(scanner);

        if (currentUser != null) {
            changeEmail(scanner);
        }

        scanner.close();
    }

    private static void login(Scanner scanner) {
        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                currentUser = email;
                break;
            } else {
                System.out.println("Invalid credentials. Please try again.");
            }
        }
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        System.out.print("Confirm password to verify ownership: ");
        String confirmPassword = scanner.nextLine();

        if (currentUser.equals(oldEmail) && users.get(currentUser).equals(confirmPassword)) {
            users.remove(currentUser);
            users.put(newEmail, confirmPassword);
            currentUser = newEmail;
            System.out.println("Your email has been successfully changed.");
        } else {
            System.out.println("Incorrect old email or confirm password. Email change failed.");
        }
    }
}