import java.util.Scanner;

public class EmailChangeApp {
    private static final String USER_EMAIL = "user@example.com";
    private static final String PASSWORD = "securepassword123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean isLoggedIn = false;
        
        while (!isLoggedIn) {
            System.out.print("Enter your email: ");
            String loginEmail = scanner.nextLine();
            System.out.print("Enter your password: ");
            String loginPassword = scanner.nextLine();

            if (USER_EMAIL.equals(loginEmail) && PASSWORD.equals(loginPassword)) {
                isLoggedIn = true;
                changeEmail(scanner);
            } else {
                System.out.println("Invalid credentials. Please try again.");
            }
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter your old email: ");
        String oldEmail = scanner.nextLine();
        if (!USER_EMAIL.equals(oldEmail)) {
            System.out.println("Old email does not match. Please try again.");
            return;
        }

        System.out.print("Enter your new email: ");
        String newEmail = scanner.nextLine();
        if (newEmail.equals(USER_EMAIL)) {
            System.out.println("New email must be different from the old email.");
            return;
        }

        System.out.print("Confirm your password: ");
        String confirmPassword = scanner.nextLine();
        if (!PASSWORD.equals(confirmPassword)) {
            System.out.println("Incorrect password. Please try again.");
            return;
        }

        System.out.println("Email successfully changed to: " + newEmail);
    }
}