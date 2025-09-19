import java.util.Scanner;

public class SimpleLoginPage {
    private static String loggedInUserEmail = "user@example.com";
    private static String userPassword = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Login Page");
        System.out.print("Enter Email: ");
        String email = scanner.nextLine();
        System.out.print("Enter Password: ");
        String password = scanner.nextLine();

        if (email.equals(loggedInUserEmail) && password.equals(userPassword)) {
            System.out.println("Login Successful!");
            changeEmail(scanner);
        } else {
            System.out.println("Invalid Email or Password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        System.out.print("Enter Old Email: ");
        String oldEmail = scanner.nextLine();
        if (!oldEmail.equals(loggedInUserEmail)) {
            System.out.println("Old email does not match the logged-in user.");
            return;
        }

        System.out.print("Enter New Email: ");
        String newEmail = scanner.nextLine();

        System.out.print("Confirm Password: ");
        String confirmPassword = scanner.nextLine();
        if (!confirmPassword.equals(userPassword)) {
            System.out.println("Incorrect password.");
            return;
        }

        loggedInUserEmail = newEmail;
        System.out.println("Email successfully changed to " + newEmail);
    }
}