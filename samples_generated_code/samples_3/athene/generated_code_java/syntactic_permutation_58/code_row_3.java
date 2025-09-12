import java.util.Scanner;

public class LoginSystem {
    private static final String USERNAME = "user";
    private static String PASSWORD = "password123";
    private static String EMAIL = "user@example.com";
    private static boolean isLoggedIn = false;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (!isLoggedIn) {
            System.out.print("Enter username: ");
            String username = scanner.nextLine();
            System.out.print("Enter password: ");
            String password = scanner.nextLine();

            if (username.equals(USERNAME) && password.equals(PASSWORD)) {
                isLoggedIn = true;
                System.out.println("Login successful!");
            } else {
                System.out.println("Invalid credentials. Please try again.");
            }
        }

        while (isLoggedIn) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (oldEmail.equals(EMAIL) && confirmPassword.equals(PASSWORD)) {
                System.out.print("Enter new email: ");
                EMAIL = scanner.nextLine();
                System.out.println("Email updated successfully!");
            } else {
                System.out.println("Incorrect old email or password. Email not changed.");
            }

            System.out.print("Do you want to change the email again? (yes/no): ");
            String continueChoice = scanner.nextLine();
            if (!continueChoice.equalsIgnoreCase("yes")) {
                break;
            }
        }

        scanner.close();
    }
}