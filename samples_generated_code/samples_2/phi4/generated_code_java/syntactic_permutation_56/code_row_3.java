import java.util.Scanner;

public class SimpleLoginPage {

    private static final String USERNAME = "user";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the login page!");

        // Login process
        boolean loggedIn = false;
        while (!loggedIn) {
            System.out.print("Enter username: ");
            String inputUsername = scanner.nextLine();
            System.out.print("Enter password: ");
            String inputPassword = scanner.nextLine();

            if (inputUsername.equals(USERNAME) && inputPassword.equals(PASSWORD)) {
                loggedIn = true;
                System.out.println("Login successful!");
            } else {
                System.out.println("Invalid username or password. Please try again.");
            }
        }

        // Update email process
        boolean updated = false;
        while (!updated) {
            System.out.print("Enter old email: ");
            String oldEmail = scanner.nextLine();
            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            if (!newEmail.equals(oldEmail)) {
                System.out.print("Confirm password: ");
                String confirmPassword = scanner.nextLine();

                // Assuming the correct password is already known after login
                System.out.print("Re-enter password for confirmation: ");
                String reEnteredPassword = scanner.nextLine();

                if (PASSWORD.equals(reEnteredPassword) && confirmPassword.equals(PASSWORD)) {
                    updated = true;
                    System.out.println("Email updated successfully from " + oldEmail + " to " + newEmail);
                } else {
                    System.out.println("Incorrect password. Please try again.");
                }
            } else {
                System.out.println("New email must be different from the old email. Please try again.");
            }
        }

        scanner.close();
    }
}