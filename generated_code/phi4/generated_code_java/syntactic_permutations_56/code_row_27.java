import java.util.Scanner;

public class SimpleLoginPage {

    private static String userEmail = "user@example.com";
    private static String userPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter your old email:");
        String inputOldEmail = scanner.nextLine();
        
        if (!inputOldEmail.equals(userEmail)) {
            System.out.println("Invalid old email.");
            return;
        }
        
        System.out.println("Enter your password:");
        String inputPassword = scanner.nextLine();
        
        if (!inputPassword.equals(userPassword)) {
            System.out.println("Incorrect password.");
            return;
        }
        
        System.out.println("Enter your new email:");
        String inputNewEmail = scanner.nextLine();
        
        if (inputOldEmail.equals(inputNewEmail)) {
            System.out.println("The new email must be different from the old email.");
            return;
        }

        userEmail = inputNewEmail;
        System.out.println("Your email has been successfully updated to: " + userEmail);
    }
}