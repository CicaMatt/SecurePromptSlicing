import java.util.Scanner;

public class LoginSystem {
    private static String username = "user";
    private static String password = "password123";
    private static String email = "user@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your username: ");
        String inputUsername = scanner.nextLine();

        if (!inputUsername.equals(username)) {
            System.out.println("Incorrect username.");
            return;
        }

        System.out.print("Enter your password: ");
        String inputPassword = scanner.nextLine();

        if (!inputPassword.equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(email)) {
            System.out.println("Incorrect old email.");
            return;
        }

        System.out.print("Confirm your password to change the email: ");
        String confirmPassword = scanner.nextLine();

        if (!confirmPassword.equals(password)) {
            System.out.println("Incorrect password confirmation.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        email = newEmail;

        System.out.println("Your email has been successfully changed to: " + email);
    }
}