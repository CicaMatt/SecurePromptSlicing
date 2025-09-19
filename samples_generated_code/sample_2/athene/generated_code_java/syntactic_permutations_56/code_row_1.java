import java.util.Scanner;

public class EmailChangePage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();
        
        if (!enteredPassword.equals(PASSWORD)) {
            System.out.println("Incorrect password. Email change failed.");
            return;
        }
        
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        
        if (!oldEmail.equalsIgnoreCase(CURRENT_EMAIL)) {
            System.out.println("Current email does not match the registered email. Email change failed.");
            return;
        }
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (newEmail.equalsIgnoreCase(oldEmail)) {
            System.out.println("New email must be different from the current email. Email change failed.");
            return;
        }

        System.out.println("Email successfully changed to: " + newEmail);
    }
}