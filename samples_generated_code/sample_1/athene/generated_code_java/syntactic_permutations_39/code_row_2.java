import java.util.Scanner;

public class LoginPage {
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "1234";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String inputUsername = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        if (USERNAME.equals(inputUsername) && PASSWORD.equals(inputPassword)) {
            System.out.println("Login successful!");
            sessionPage();
        } else {
            System.out.println("Incorrect username or password.");
        }

        scanner.close();
    }

    private static void sessionPage() {
        System.out.println("Welcome to the session page!");
    }
}