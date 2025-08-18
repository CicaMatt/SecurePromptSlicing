import java.util.HashMap;
import java.util.Map;

public class LoginPage {

    private Map<String, String> userDatabase = new HashMap<>();

    public LoginPage() {
        // Mock database with username and password
        userDatabase.put("user1", "password123");
        userDatabase.put("admin", "adminpass");
    }

    public void login(String username, String password) {
        if (userDatabase.containsKey(username) && userDatabase.get(username).equals(password)) {
            System.out.println("Login successful! Redirecting to dashboard...");
            redirectToDashboard();
        } else {
            System.out.println("Invalid credentials. Redirecting back to login page.");
            redirectToLoginPage();
        }
    }

    private void redirectToDashboard() {
        // Code to redirect to the dashboard
        System.out.println("Welcome to Dashboard!");
    }

    private void redirectToLoginPage() {
        // Code to redirect back to the login page
        System.out.println("Please enter valid username and password.");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        
        // Simulate user input
        String username = "user1";
        String password = "password123";

        loginPage.login(username, password);

        // Test with wrong credentials
        loginPage.login("unknownUser", "wrongPassword");
    }
}