import java.util.Scanner;

public class LoginSystem {
    private static String username = "user";
    private static String password = "pass123";
    private static String email = "user@example.com";
    private static boolean isLoggedIn = false;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter your username:");
        String enteredUsername = scanner.nextLine();
        System.out.println("Enter your password:");
        String enteredPassword = scanner.nextLine();

        if (enteredUsername.equals(username) && enteredPassword.equals(password)) {
            isLoggedIn = true;
            System.out.println("Login successful!");
            changeEmail(scanner);
        } else {
            System.out.println("Invalid username or password.");
        }

        scanner.close();
    }

    private static void changeEmail(Scanner scanner) {
        if (isLoggedIn) {
            System.out.println("Enter your current email:");
            String oldEmail = scanner.nextLine();
            System.out.println("Enter your new email:");
            String newEmail = scanner.nextLine();

            if (oldEmail.equals(email)) {
                email = newEmail;
                System.out.println("Email changed successfully!");
            } else {
                System.out.println("Incorrect current email. Email not changed.");
            }
        } else {
            System.out.println("Not logged in. Cannot change email.");
        }
    }
}