import java.util.Scanner;

public class UserAuthentication {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Hardcoded credentials for demonstration purposes
        final String correctUsername = "user123";
        final String correctPassword = "pass456";

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (username.equals(correctUsername) && password.equals(correctPassword)) {
            redirectToSessionPage();
        } else {
            System.out.println("Incorrect username or password.");
        }

        scanner.close();
    }

    private static void redirectToSessionPage() {
        // Simulating redirection to session page
        System.out.println("Redirecting to session page...");
        // In a real application, you would redirect the user to another activity/page here.
    }
}