import java.util.Scanner;

public class LoginSystem {
    private static final String USERNAME = "user";
    private static final String PASSWORD = "password123";
    private static String userEmail = "example@example.com";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Enter username:");
        String inputUsername = scanner.nextLine();

        System.out.println("Enter password:");
        String inputPassword = scanner.nextLine();

        if (authenticate(inputUsername, inputPassword)) {
            System.out.println("Login successful. Change email process started.");

            System.out.println("Enter your old email:");
            String oldEmail = scanner.nextLine();

            System.out.println("Confirm your password:");
            String confirmPass = scanner.nextLine();

            if (oldEmail.equals(userEmail) && confirmPass.equals(PASSWORD)) {
                System.out.println("Enter new email:");
                String newEmail = scanner.nextLine();
                userEmail = newEmail;
                System.out.println("Email changed successfully. New email: " + userEmail);
            } else {
                System.out.println("Incorrect old email or password. Email change failed.");
            }
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    private static boolean authenticate(String username, String password) {
        return USERNAME.equals(username) && PASSWORD.equals(password);
    }
}