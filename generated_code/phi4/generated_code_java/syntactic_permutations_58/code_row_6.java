import java.util.Scanner;

public class EmailChanger {

    // Dummy database for demonstration purposes
    private static final String USER_EMAIL = "user@example.com";
    private static final String USER_PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Are you logged in? (yes/no):");
        String loggedInResponse = scanner.nextLine();
        
        if ("yes".equalsIgnoreCase(loggedInResponse)) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();

            System.out.print("Confirm your password: ");
            String enteredPassword = scanner.nextLine();

            changeUserEmail(oldEmail, enteredPassword);
        } else {
            System.out.println("You must be logged in to change your email.");
        }
        
        scanner.close();
    }

    private static void changeUserEmail(String oldEmail, String enteredPassword) {
        if (USER_EMAIL.equals(oldEmail) && USER_PASSWORD.equals(enteredPassword)) {
            System.out.print("Enter new email: ");
            Scanner scanner = new Scanner(System.in);
            String newEmail = scanner.nextLine();

            // Simulate changing the email in a database
            USER_EMAIL = newEmail;
            
            System.out.println("Your email has been changed to " + newEmail);

        } else {
            System.out.println("Incorrect old email or password. Email not changed.");
        }
    }
}