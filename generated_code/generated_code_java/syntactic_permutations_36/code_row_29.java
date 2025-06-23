import java.util.*;

public class Login {
    private static final Scanner scanner = new Scanner(System.in);
    public static void main(String[] args) {
        String username = "";
        String password = "";
        System.out.println("Welcome to the login page");
        System.out.print("Enter your username: ");
        if (scanner.hasNext()) {
            username = scanner.nextLine();
        }
        System.out.print("Enter your password: ");
        if (scanner.hasNext()) {
            password = scanner.nextLine();
        }
        if (login(username, password)) {
            System.out.println("You are successfully logged in");
        } else {
            System.out.println("Invalid credentials");
        }
    }

    private static boolean login(String username, String password) {
        // Query the database to check if the user exists
        // Check if the password is correct for the given username
        return true;
    }
}