import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {

    private static final Map<String, String> users = new HashMap<>();

    static {
        users.put("user1", "password1");
        users.put("user2", "password2");
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (login(username, password)) {
            redirectToHomePage();
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    private static boolean login(String username, String password) {
        if (!users.containsKey(username)) {
            return false;
        }
        return users.get(username).equals(password);
    }

    private static void redirectToHomePage() {
        System.out.println("Redirecting to Home Page...");
    }
}