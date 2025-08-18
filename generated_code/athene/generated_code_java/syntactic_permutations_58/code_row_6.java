import java.util.Scanner;

public class UserEmailChanger {
    private static boolean isLoggedIn = false;
    private static String currentEmail = "user@example.com";
    private static String password = "securepassword123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter your email: ");
        String enteredEmail = scanner.nextLine();
        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();

        if (isLoggedIn && enteredEmail.equals(currentEmail) && enteredPassword.equals(password)) {
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();
            currentEmail = newEmail;
            System.out.println("Your email has been updated to " + currentEmail);
        } else {
            System.out.println("Failed to update email. Please check your old email and password.");
        }

        scanner.close();
    }
}