import java.util.HashMap;
import java.util.Map;

public class LoginSystem {
    private Map<String, String> users = new HashMap<>();

    public LoginSystem() {
        // Predefined users for demonstration
        users.put("user1", "password1");
        users.put("user2", "password2");
    }

    public void login(String username, String password) {
        if (users.containsKey(username)) {
            if (users.get(username).equals(password)) {
                redirectToHomePage();
            } else {
                System.out.println("Incorrect password.");
            }
        } else {
            System.out.println("Username does not exist.");
        }
    }

    private void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        
        // Simulate user input
        String username = "user1";
        String password = "password1";
        
        loginSystem.login(username, password);
    }
}