import java.util.Scanner;

public class SimpleLogin {

    private static String currentEmail = "user@example.com";
    private static final String confirmPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();

        if (!oldEmail.equals(currentEmail)) {
            System.out.println("Incorrect email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm password: ");
        String inputPassword = scanner.nextLine();

        if (!inputPassword.equals(confirmPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        currentEmail = newEmail;
        System.out.println("Your email has been changed successfully to " + newEmail);
    }
}