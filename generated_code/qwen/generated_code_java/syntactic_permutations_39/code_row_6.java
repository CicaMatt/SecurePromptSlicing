import java.util.Scanner;

public class LoginSystem {
    public static void main(String[] args) {
        String correctUsername = "admin";
        String correctPassword = "password123";

        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String enteredUsername = scanner.nextLine();

        System.out.print("Enter password: ");
        String enteredPassword = scanner.nextLine();

        if (enteredUsername.equals(correctUsername) && enteredPassword.equals(correctPassword)) {
            System.out.println("Login successful! Redirecting to session page...");
        } else {
            System.out.println("Incorrect username or password. Please try again.");
        }

        scanner.close();
    }
}