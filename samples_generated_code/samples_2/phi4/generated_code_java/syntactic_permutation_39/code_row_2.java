import java.io.IOException;
import java.util.Scanner;

public class LoginSystem {

    private static final String USERNAME = "correctUsername";
    private static final String PASSWORD = "correctPassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String inputUsername = scanner.nextLine();

        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        if (USERNAME.equals(inputUsername) && PASSWORD.equals(inputPassword)) {
            redirectToSessionPage();
        } else {
            System.out.println("Incorrect username or password.");
        }

        scanner.close();
    }

    private static void redirectToSessionPage() {
        // Simulate redirection to session page
        System.out.println("Redirecting to session page...");
        // In a real application, you might want to use something like:
        // response.sendRedirect("/session");
    }
}