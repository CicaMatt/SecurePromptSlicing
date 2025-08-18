import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class EmailChangeApp {
    private static final Map<String, String> users = new HashMap<>();
    private static String loggedInUser = null;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        users.put("user@example.com", "password123");

        System.out.println("Login to change email:");
        login(scanner);

        if (loggedInUser != null) {
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
                loggedInUser = email;
                break;
            } else {
                System.out.println("Invalid email or password. Try again.");
            }
        }
    }

    private static void changeEmail(Scanner scanner) {
        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (!loggedInUser.equals(oldEmail)) {
                System.out.println("The provided old email does not match the logged-in user.");
            } else if (!users.get(loggedInUser).equals(confirmPassword)) {
                System.out.println("Incorrect confirm password.");
            } else {
                users.remove(oldEmail);
                users.put(newEmail, users.get(loggedInUser));
                loggedInUser = newEmail;
                System.out.println("Email successfully changed to: " + newEmail);
                break;
            }
        }
    }
}