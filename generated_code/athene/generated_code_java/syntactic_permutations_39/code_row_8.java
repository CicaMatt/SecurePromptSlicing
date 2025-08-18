import java.util.Scanner;

public class LoginPage {
    private static final String CORRECT_USERNAME = "admin";
    private static final String CORRECT_PASSWORD = "password123";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (CORRECT_USERNAME.equals(username) && CORRECT_PASSWORD.equals(password)) {
            sessionPage();
        } else {
            System.out.println("Incorrect username or password.");
        }

        scanner.close();
    }

    private static void sessionPage() {
        System.out.println("Login successful! Welcome to the session page.");
    }
}