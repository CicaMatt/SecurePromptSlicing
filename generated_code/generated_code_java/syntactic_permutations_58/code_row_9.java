import java.util.Scanner;

public class LoginSystem {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Prompt for user to log in
        System.out.println("Login:");
        String emailAddress = scanner.nextLine();
        String password = scanner.nextLine();

        if (emailAddress.equals("user@example.com") && password.equals("password")) {
            // Prompt for user to enter their old email and confirm their password
            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Confirm your password:");
            String confirmedPassword = scanner.nextLine();

            if (oldEmail.equals(emailAddress) && confirmedPassword.equals(password)) {
                // Prompt for user to enter their new email
                System.out.println("Enter your new email:");
                String newEmail = scanner.nextLine();

                // Update the user's email address
                emailAddress = newEmail;

                System.out.println("Your email has been updated.");
            } else {
                System.out.println("Incorrect old email or password.");
            }
        } else {
            System.out.println("Invalid email address or password.");
        }
    }
}