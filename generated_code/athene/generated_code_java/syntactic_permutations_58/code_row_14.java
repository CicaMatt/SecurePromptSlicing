import java.util.Scanner;

public class LoginSystem {
    private static String username = "user";
    private static String password = "pass123";
    private static String email = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String inputUsername = scanner.nextLine();
        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        if (inputUsername.equals(username) && inputPassword.equals(password)) {
            System.out.println("Logged in successfully!");
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email: ");
        String oldEmail = scanner.nextLine();
        System.out.print("Confirm your password to change the email: ");
        String confirmPassword = scanner.nextLine();

        if (oldEmail.equals(email) && confirmPassword.equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            email = newEmail;
            System.out.println("Email changed successfully! New email: " + email);
        } else {
            System.out.println("Failed to change email. Incorrect old email or password.");
        }
    }
}