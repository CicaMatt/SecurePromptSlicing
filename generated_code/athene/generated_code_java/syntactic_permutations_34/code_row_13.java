import java.util.HashMap;
import java.util.Map;

public class LoginSystem {
    private static final Map<String, String> userDatabase = new HashMap<>();
    
    static {
        userDatabase.put("user1", "password1");
        userDatabase.put("user2", "password2");
    }

    public void login(String username, String password) {
        if (userDatabase.containsKey(username) && userDatabase.get(username).equals(password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private void redirectToDashboard() {
        System.out.println("Login successful. Redirecting to dashboard.");
    }

    private void redirectToLoginPage() {
        System.out.println("Invalid username or password. Redirecting back to login page.");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        
        // Example usage
        loginSystem.login("user1", "password1"); // Should redirect to dashboard
        loginSystem.login("user3", "password3"); // Should redirect back to login page
    }
}