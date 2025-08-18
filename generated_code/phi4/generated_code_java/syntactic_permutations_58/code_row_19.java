import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class SimpleLoginSystem {
    private static Map<String, String> users = new HashMap<>();
    
    public static void main(String[] args) {
        users.put("user1", "password123"); // Sample user data

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        if (isUserLoggedIn(username, scanner)) {
            changeEmail(username, scanner);
        }
    }

    private static boolean isUserLoggedIn(String username, Scanner scanner) {
        if (!users.containsKey(username)) {
            System.out.println("Username not found.");
            return false;
        }

        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();

        if (users.get(username).equals(enteredPassword)) {
            System.out.println("Login successful.");
            return true;
        } else {
            System.out.println("Incorrect password.");
            return false;
        }
    }

    private static void changeEmail(String username, Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();

        if (users.get(username).equals(confirmPassword)) {
            // Assuming the email is simply stored as a value in the map for simplicity
            users.put(username, "newemail@example.com");
            System.out.println("Email changed successfully.");
        } else {
            System.out.println("Incorrect password. Email not changed.");
        }
    }
}