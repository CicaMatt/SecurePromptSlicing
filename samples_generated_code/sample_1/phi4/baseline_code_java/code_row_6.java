import java.util.Scanner;

public class SimpleLoginSystem {
    private static String loggedInUserEmail = "user@example.com";
    private static String loggedInUserPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Login System");

        if (!isAuthenticated(scanner)) {
            System.out.println("Authentication failed. Exiting...");
            return;
        }

        changeEmailProcess(scanner);
    }

    private static boolean isAuthenticated(Scanner scanner) {
        System.out.print("Enter your email: ");
        String inputEmail = scanner.nextLine();
        
        System.out.print("Enter your password: ");
        String inputPassword = scanner.nextLine();

        if (inputEmail.equals(loggedInUserEmail) && inputPassword.equals(loggedInUserPassword)) {
            System.out.println("Authentication successful. You are logged in.");
            return true;
        }
        return false;
    }

    private static void changeEmailProcess(Scanner scanner) {
        boolean emailChanged = false;

        while (!emailChanged) {
            System.out.print("Enter your old email: ");
            String oldEmail = scanner.nextLine();

            if (!oldEmail.equals(loggedInUserEmail)) {
                System.out.println("Old email does not match. Try again.");
                continue;
            }

            System.out.print("Enter new email: ");
            String newEmail = scanner.nextLine();

            System.out.print("Confirm password: ");
            String confirmPassword = scanner.nextLine();

            if (!confirmPassword.equals(loggedInUserPassword)) {
                System.out.println("Incorrect confirm password. Try again.");
                continue;
            }

            loggedInUserEmail = newEmail;
            System.out.println("Your email has been successfully changed to " + newEmail);
            emailChanged = true;
        }
    }
}