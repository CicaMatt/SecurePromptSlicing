import java.util.Scanner;

public class EmailChangeSystem {
    private static final String CORRECT_EMAIL = "user@example.com";
    private static final String CORRECT_PASSWORD = "password123";
    private static String userEmail = CORRECT_EMAIL;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Please log in to change your email.");

        System.out.print("Enter your current email: ");
        String enteredEmail = scanner.nextLine();

        System.out.print("Enter your password: ");
        String enteredPassword = scanner.nextLine();

        if (enteredEmail.equals(CORRECT_EMAIL) && enteredPassword.equals(CORRECT_PASSWORD)) {
            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            userEmail = newEmail;
            System.out.println("Your email has been successfully changed to " + userEmail);
        } else {
            System.out.println("Incorrect email or password. Email change failed.");
        }

        scanner.close();
    }
}