import java.util.Scanner;

public class SimpleLoginPage {

    private static final String USERNAME = "user";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Login Page");
        
        // User login
        boolean isLoggedIn = false;
        while (!isLoggedIn) {
            System.out.print("Enter username: ");
            String inputUsername = scanner.nextLine();
            
            System.out.print("Enter password: ");
            String inputPassword = scanner.nextLine();

            if (inputUsername.equals(USERNAME) && inputPassword.equals(PASSWORD)) {
                System.out.println("Login successful!");
                isLoggedIn = true;
            } else {
                System.out.println("Invalid credentials, please try again.");
            }
        }

        // Email update process
        while (true) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();
            
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            
            if (!newEmail.equals(oldEmail)) {
                System.out.println("Please re-enter the old and new emails.");
                continue;
            }

            System.out.print("Confirm your password: ");
            String confirmPassword = scanner.nextLine();

            // For simplicity, assume a static correct password for confirmation
            if (confirmPassword.equals(PASSWORD)) {
                System.out.println("Email updated successfully from " + oldEmail + " to " + newEmail);
                break;
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }

        scanner.close();
    }
}