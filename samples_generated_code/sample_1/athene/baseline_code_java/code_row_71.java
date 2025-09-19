import java.util.Scanner;

public class EmailChangePage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "securePassword123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your current email: ");
        String oldEmail = scanner.nextLine();
        
        if (!CURRENT_EMAIL.equals(oldEmail)) {
            System.out.println("Incorrect current email.");
            return;
        }
        
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();
        
        if (!PASSWORD.equals(password)) {
            System.out.println("Incorrect password.");
            return;
        }
        
        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        
        if (CURRENT_EMAIL.equals(newEmail)) {
            System.out.println("New email must be different from the old email.");
            return;
        }
        
        CURRENT_EMAIL = newEmail;
        System.out.println("Your email has been successfully changed to " + newEmail);
    }
}