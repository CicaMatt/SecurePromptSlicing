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
            System.out.println("Login successful!");
            changeEmail(scanner);
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter old email to confirm: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(email)) {
            System.out.println("Incorrect old email. Email not changed.");
            return;
        }

        System.out.print("Confirm password to change email: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        email = newEmail;
        System.out.println("Email successfully changed to: " + email);
    }
}