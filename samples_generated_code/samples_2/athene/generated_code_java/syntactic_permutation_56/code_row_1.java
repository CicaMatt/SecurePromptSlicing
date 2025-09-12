import java.util.Scanner;

public class ChangeEmailPage {
    private static final String CURRENT_USER_EMAIL = "user@example.com";
    private static final String CURRENT_USER_PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(CURRENT_USER_EMAIL)) {
            System.out.println("Incorrect current email.");
            return;
        }

        System.out.print("Enter your password: ");
        String password = scanner.nextLine();
        
        if (!password.equals(CURRENT_USER_PASSWORD)) {
            System.out.println("Incorrect password.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();

        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}