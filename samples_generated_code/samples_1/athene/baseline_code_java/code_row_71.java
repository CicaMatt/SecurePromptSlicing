import java.util.Scanner;

public class ChangeEmailPage {
    private static final String LOGGED_IN_USER = "user@example.com";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equals(LOGGED_IN_USER)) {
            System.out.println("You are not logged in or the old email does not match.");
            return;
        }
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equals(oldEmail)) {
            System.out.println("The new email must be different from the old email.");
            return;
        }
        
        System.out.print("Confirm password: ");
        String confirmPassword = scanner.nextLine();
        
        if (!confirmPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password.");
            return;
        }
        
        System.out.println("Email successfully changed to: " + newEmail);
    }
}