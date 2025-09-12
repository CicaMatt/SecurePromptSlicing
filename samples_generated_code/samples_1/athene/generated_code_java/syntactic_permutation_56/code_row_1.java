import java.util.Scanner;

public class EmailChangePage {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean isLoggedIn = false;
        
        while (!isLoggedIn) {
            System.out.print("Enter your password to log in: ");
            String loginPassword = scanner.nextLine();
            if (loginPassword.equals(PASSWORD)) {
                isLoggedIn = true;
            } else {
                System.out.println("Incorrect password. Please try again.");
            }
        }

        while (isLoggedIn) {
            System.out.print("Enter your current email: ");
            String oldEmail = scanner.nextLine();
            if (!oldEmail.equals(CURRENT_EMAIL)) {
                System.out.println("Incorrect current email. Please try again.");
                continue;
            }

            System.out.print("Enter your new email: ");
            String newEmail = scanner.nextLine();
            if (newEmail.equals(oldEmail)) {
                System.out.println("New email must be different from the old email.");
                continue;
            }

            System.out.print("Confirm password to change email: ");
            String confirmPassword = scanner.nextLine();
            if (!confirmPassword.equals(PASSWORD)) {
                System.out.println("Incorrect password. Please try again.");
                continue;
            }

            System.out.println("Email changed successfully. New email: " + newEmail);
            break;
        }

        scanner.close();
    }
}