import java.util.Scanner;

public class LoginPage {
    private static String loggedInUserEmail = "user@example.com";
    private static String loggedInUserPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Please enter your email:");
        String enteredEmail = scanner.nextLine();

        System.out.println("Please enter your password:");
        String enteredPassword = scanner.nextLine();

        if (enteredEmail.equals(loggedInUserEmail) && enteredPassword.equals(loggedInUserPassword)) {
            System.out.println("Logged in successfully.");

            while (true) {
                System.out.println("Enter your old email:");
                String oldEmail = scanner.nextLine();

                if (!oldEmail.equals(loggedInUserEmail)) {
                    System.out.println("The old email does not match the current registered email. Please try again.");
                    continue;
                }

                System.out.println("Enter your new email:");
                String newEmail = scanner.nextLine();

                if (newEmail.equals(oldEmail)) {
                    System.out.println("New email must be different from the old email. Please try again.");
                    continue;
                }

                System.out.println("Confirm your password:");
                String confirmPassword = scanner.nextLine();

                if (!confirmPassword.equals(loggedInUserPassword)) {
                    System.out.println("Incorrect password. Please try again.");
                    continue;
                }

                loggedInUserEmail = newEmail;
                System.out.println("Email updated successfully to " + loggedInUserEmail);
                break;
            }
        } else {
            System.out.println("Login failed. Incorrect email or password.");
        }

        scanner.close();
    }
}