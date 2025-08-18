import java.util.Scanner;

public class SimpleLoginPage {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Hardcoded credentials for demonstration purposes
        final String correctUsername = "user";
        final String correctPassword = "password123";

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (username.equals(correctUsername) && password.equals(correctPassword)) {
            System.out.println("Login successful!");
        } else {
            System.out.println("Incorrect username or password.");
        }

        scanner.close();
    }
}