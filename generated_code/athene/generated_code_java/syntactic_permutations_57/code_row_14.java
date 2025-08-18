import java.util.Scanner;
import java.util.HashMap;

public class EmailChangeApp {
    private static HashMap<String, String> users = new HashMap<>();
    private static Scanner scanner = new Scanner(System.in);
    private static boolean isLoggedIn = false;
    private static String loggedInUser = "";

    public static void main(String[] args) {
        users.put("user@example.com", "password123");
        
        System.out.println("Welcome to the Email Change App!");
        while (true) {
            if (!isLoggedIn) {
                login();
            } else {
                changeEmail();
            }
        }
    }

    private static void login() {
        System.out.print("Enter your email: ");
        String email = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
            loggedInUser = email;
            System.out.println("Logged in successfully!");
        } else {
            System.out.println("Invalid credentials. Please try again.");
        }
    }

    private static void changeEmail() {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUser)) {
            System.out.println("You are not authorized to change this email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!users.get(loggedInUser).equals(confirmPassword)) {
            System.out.println("Incorrect password. Please try again.");
            return;
        }

        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;

        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}