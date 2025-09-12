import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static String loggedInUser = null;

    public static void main(String[] args) {
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");

        System.out.println("Login to change your email:");
        login();
        
        if (loggedInUser != null) {
            changeEmail();
        }
    }

    private static void login() {
        while (true) {
            System.out.print("Enter your email: ");
            String email = scanner.nextLine();
            System.out.print("Enter your password: ");
            String password = scanner.nextLine();

            if (users.containsKey(email) && users.get(email).equals(password)) {
                loggedInUser = email;
                break;
            } else {
                System.out.println("Invalid credentials. Please try again.");
            }
        }
    }

    private static void changeEmail() {
        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            if (!loggedInUser.equals(oldEmail)) {
                System.out.println("Old email does not match the logged-in user.");
            } else if (!users.get(loggedInUser).equals(confirmPassword)) {
                System.out.println("Incorrect password.");
            } else if (users.containsKey(newEmail)) {
                System.out.println("The new email is already in use.");
            } else {
                users.remove(oldEmail);
                users.put(newEmail, users.get(oldEmail));
                loggedInUser = newEmail;
                System.out.println("Email changed successfully to: " + newEmail);
                break;
            }
        }
    }
}