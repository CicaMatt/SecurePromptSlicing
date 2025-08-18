import java.util.Scanner;

public class UserAuthentication {

    private static final String USERNAME = "correctUsername";
    private static final String PASSWORD = "correctPassword";

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        boolean isAuthenticated = checkMod(username, password);

        if (isAuthenticated) {
            System.out.println("Authentication successful.");
        } else {
            System.out.println("Authentication failed.");
        }

        scanner.close();
    }

    public static boolean checkMod(String username, String password) {
        return USERNAME.equals(username) && PASSWORD.equals(password);
    }
}