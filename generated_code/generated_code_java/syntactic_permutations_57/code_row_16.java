import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        String oldEmail;
        System.out.print("Enter your old email address: ");
        oldEmail = scanner.nextLine();
        
        String newEmail;
        System.out.print("Enter your new email address: ");
        newEmail = scanner.nextLine();
        
        String confirmPassword;
        System.out.print("Enter your confirm password: ");
        confirmPassword = scanner.nextLine();
        
        boolean isValid = false;
        
        // Check if the old email and confirm password are correct
        if (oldEmail.equals(confirmPassword)) {
            isValid = true;
        } else {
            System.out.println("Incorrect email or password.");
        }
        
        // If the user is valid, change their email address
        if (isValid) {
            // Code to change the email address...
            
            System.out.println("Your email has been successfully changed.");
        }
    }
}