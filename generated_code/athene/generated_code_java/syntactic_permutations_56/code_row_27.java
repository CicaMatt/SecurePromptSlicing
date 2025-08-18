import java.util.Scanner;

public class ChangeEmailPage {
    private static final String CURRENT_EMAIL = "example@example.com";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        
        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();
        
        if (!CURRENT_EMAIL.equals(oldEmail) || !PASSWORD.equals(enteredPassword)) {
            System.out.println("Incorrect email or password.");
            return;
        }
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equals(oldEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        CURRENT_EMAIL = newEmail; // In a real application, you would update this in a database.
        System.out.println("Your email has been successfully changed to: " + newEmail);
    }
}