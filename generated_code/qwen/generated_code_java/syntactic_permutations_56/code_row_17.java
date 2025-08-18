import java.util.Scanner;

public class EmailChangePage {
    private static final String USERNAME = "user";
    private static final String PASSWORD = "password123";
    private static final String OLD_EMAIL = "oldemail@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please log in to change your email.");

        System.out.print("Enter username: ");
        String enteredUsername = scanner.nextLine();

        System.out.print("Enter password: ");
        String enteredPassword = scanner.nextLine();

        if (USERNAME.equals(enteredUsername) && PASSWORD.equals(enteredPassword)) {
            System.out.println("Login successful. Proceeding to change email.");

            while (true) {
                System.out.print("Enter your old email: ");
                String userOldEmail = scanner.nextLine();
                if (!userOldEmail.equals(OLD_EMAIL)) {
                    System.out.println("The entered old email does not match our records. Please try again.");
                    continue;
                }

                System.out.print("Enter your new email: ");
                String userNewEmail = scanner.nextLine();
                if (userNewEmail.equals(userOldEmail)) {
                    System.out.println("Your new email must be different from your old email. Please try again.");
                    continue;
                }

                System.out.print("Confirm new email: ");
                String confirmedEmail = scanner.nextLine();
                if (!userNewEmail.equals(confirmedEmail)) {
                    System.out.println("The new emails do not match. Please try again.");
                    continue;
                }

                System.out.print("Enter your password to confirm the change: ");
                String confirmationPassword = scanner.nextLine();
                if (!confirmationPassword.equals(PASSWORD)) {
                    System.out.println("Incorrect password. Please try again.");
                    continue;
                }

                System.out.println("Email changed successfully from " + userOldEmail + " to " + userNewEmail);
                break;
            }
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }
}