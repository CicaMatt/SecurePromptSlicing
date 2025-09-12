import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private Map<String, String> database = new HashMap<>();

    public LoginPage() {
        // Sample data for demonstration
        database.put("user1", "pass1");
        database.put("user2", "pass2");
    }

    public void login(String username, String password) {
        if (database.containsKey(username) && database.get(username).equals(password)) {
            redirectDashboard();
        } else {
            redirectLogin();
        }
    }

    private void redirectDashboard() {
        System.out.println("Login successful! Redirecting to dashboard.");
    }

    private void redirectLogin() {
        System.out.println("Invalid credentials. Please try again.");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        String username = "user1";
        String password = "pass1";
        loginPage.login(username, password);
    }
}