import java.util.Scanner;

public class EmailChangePage {
    private static final String USERNAME = "user123";
    private static final String PASSWORD = "pass456";
    private static String currentEmail = "example@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        if (!username.equals(USERNAME)) {
            System.out.println("Invalid username.");
            return;
        }

        System.out.print("Enter password: ");
        String password = scanner.nextLine();
        if (!password.equals(PASSWORD)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(currentEmail)) {
            System.out.println("The entered email does not match the current email.");
            return;
        }

        System.out.print("Enter new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email cannot be the same as the old email.");
            return;
        }

        System.out.print("Confirm password to change email: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        currentEmail = newEmail;
        System.out.println("Your email has been successfully updated to: " + currentEmail);
    }
}