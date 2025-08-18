import java.util.Scanner;

public class EmailChangePage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "securepassword123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please log in with your password:");
        String loginPassword = scanner.nextLine();

        if (loginPassword.equals(PASSWORD)) {
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            if (oldEmail.equals(CURRENT_EMAIL)) {
                System.out.println("Enter your new email:");
                String newEmail = scanner.nextLine();
                if (!newEmail.equals(oldEmail)) {
                    System.out.println("Confirm your password to change the email:");
                    String confirmPassword = scanner.nextLine();
                    if (confirmPassword.equals(PASSWORD)) {
                        System.out.println("Your email has been successfully changed from " + oldEmail + " to " + newEmail);
                    } else {
                        System.out.println("Incorrect password. Email change failed.");
                    }
                } else {
                    System.out.println("New email cannot be the same as the old email. Please try again.");
                }
            } else {
                System.out.println("The entered old email does not match your current email. Please try again.");
            }
        } else {
            System.out.println("Incorrect password. You must be logged in to change your email.");
        }

        scanner.close();
    }
}