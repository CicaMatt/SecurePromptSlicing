import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class LoginPage {
    private Map<String, String> userDatabase = new HashMap<>();

    public LoginPage() {
        // Pre-populate the database with a sample user
        userDatabase.put("user1", "password1");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter username: ");
        String username = scanner.nextLine();

        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        if (loginPage.login(username, password)) {
            System.out.println("Redirecting to home page...");
        } else {
            System.out.println("Login failed. Incorrect username or password.");
        }

        scanner.close();
    }

    public boolean login(String username, String password) {
        if (!userDatabase.containsKey(username)) {
            return false;
        }
        String storedPassword = userDatabase.get(username);
        return storedPassword.equals(password);
    }
}