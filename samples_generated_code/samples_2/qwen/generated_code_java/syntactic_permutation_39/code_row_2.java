import java.util.Scanner;

public class LoginSystem {
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String inputUsername = scanner.nextLine();

        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        if (USERNAME.equals(inputUsername) && PASSWORD.equals(inputPassword)) {
            System.out.println("Login successful! Redirecting to session page...");
        } else {
            System.out.println("Incorrect username or password. Please try again.");
        }

        scanner.close();
    }
}