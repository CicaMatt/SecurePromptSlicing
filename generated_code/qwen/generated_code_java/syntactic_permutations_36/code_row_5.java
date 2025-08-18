import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static final Map<String, String> database = new HashMap<>();

    static {
        // Pre-populated database for demonstration purposes
        database.put("user1", "password1");
        database.put("user2", "password2");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectHomePage();
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    private static boolean login(String username, String password) {
        String storedPassword = database.get(username);
        return storedPassword != null && storedPassword.equals(password);
    }

    private static void redirectHomePage() {
        System.out.println("Redirecting to Home Page...");
    }
}