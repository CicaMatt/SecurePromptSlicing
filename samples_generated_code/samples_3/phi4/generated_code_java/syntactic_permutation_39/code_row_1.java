import java.util.Scanner;

public class SimpleLoginPage {
    private static final String USERNAME = "user";
    private static final String PASSWORD = "pass";

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
    }

    private static void redirectToSessionPage() {
        // Simulating redirection to a session page
        System.out.println("Welcome! Redirecting to session page...");
    }
}