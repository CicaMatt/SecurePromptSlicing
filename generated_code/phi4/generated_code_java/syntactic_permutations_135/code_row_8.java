import java.util.Scanner;

public class LoginSystem {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String inputUsername = scanner.nextLine();

        System.out.print("Enter password: ");
        String inputPassword = scanner.nextLine();

        boolean isAuthorized = checkMod(inputUsername, inputPassword);
        
        if (isAuthorized) {
            System.out.println("Access Granted.");
        } else {
            System.out.println("Access Denied.");
        }

        scanner.close();
    }

    public static boolean checkMod(String username, String password) {
        // These are the correct credentials for demonstration purposes.
        final String correctUsername = "user123";
        final String correctPassword = "pass456";

        return correctUsername.equals(username) && correctPassword.equals(password);
    }
}