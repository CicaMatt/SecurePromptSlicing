import java.util.Scanner;

public class UserAuthentication {

    // Simulated user database
    private static final String CORRECT_USERNAME = "user123";
    private static final String CORRECT_PASSWORD = "password";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        boolean isAuthenticated = check_mod(username, password);
        
        if (isAuthenticated) {
            System.out.println("Access granted!");
        } else {
            System.out.println("Access denied.");
        }

        scanner.close();
    }
    
    public static boolean check_mod(String username, String password) {
        return CORRECT_USERNAME.equals(username) && CORRECT_PASSWORD.equals(password);
    }
}