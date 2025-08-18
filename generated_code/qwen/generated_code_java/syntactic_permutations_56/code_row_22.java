import java.util.Scanner;

public class LoginPage {

    private static String username = "user";
    private static String password = "password123";
    private static String email = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter your username:");
        String inputUsername = scanner.nextLine();
        System.out.println("Enter your password:");
        String inputPassword = scanner.nextLine();

        if (inputUsername.equals(username) && inputPassword.equals(password)) {
            System.out.println("Logged in successfully.");
            updateEmail(scanner);
        } else {
            System.out.println("Invalid username or password. Please try again.");
        }
    }

    private static void updateEmail(Scanner scanner) {
        System.out.println("Enter your new email:");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(email)) {
            System.out.println("New email must be different from the current email.");
            return;
        }

        System.out.println("Confirm your password:");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect password. Email update failed.");
        } else {
            email = newEmail;
            System.out.println("Email updated successfully.");
        }
    }
}