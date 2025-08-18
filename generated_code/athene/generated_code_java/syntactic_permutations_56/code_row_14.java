import java.util.Scanner;

public class EmailChangeApp {
    private static final String CURRENT_EMAIL = "user@example.com";
    private static final String PASSWORD = "securepassword123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean isLoggedIn = false;
        
        while (!isLoggedIn) {
            System.out.print("Enter your email: ");
            String loginEmail = scanner.nextLine();
            System.out.print("Enter your password: ");
            String loginPassword = scanner.nextLine();

            if (CURRENT_EMAIL.equals(loginEmail) && PASSWORD.equals(loginPassword)) {
                isLoggedIn = true;
                changeEmail(scanner);
            } else {
                System.out.println("Invalid email or password. Please try again.");
            }
        }
        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!CURRENT_EMAIL.equals(oldEmail)) {
            System.out.println("The old email does not match the current email.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(CURRENT_EMAIL)) {
            System.out.println("The new email must be different from the old email.");
            return;
        }

        System.out.print("Confirm your password to change the email: ");
        String confirmPassword = scanner.nextLine();
        if (!PASSWORD.equals(confirmPassword)) {
            System.out.println("Incorrect password. Email not changed.");
            return;
        }

        System.out.println("Email successfully changed from " + CURRENT_EMAIL + " to " + newEmail);
    }
}