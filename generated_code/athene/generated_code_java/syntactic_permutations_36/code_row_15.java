import java.util.HashMap;
import java.util.Map;

public class LoginSystem {
    private Map<String, String> users = new HashMap<>();

    public LoginSystem() {
        // Example users for demonstration
        users.put("user1", "password1");
        users.put("user2", "password2");
    }

    public void login(String username, String password) {
        if (users.containsKey(username)) {
            if (users.get(username).equals(password)) {
                redirectToHomePage();
            } else {
                return;
            }
        } else {
            return;
        }
    }

    private void redirectToHomePage() {
        System.out.println("Redirecting to home page...");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        String username = "user1";
        String password = "password1";
        loginSystem.login(username, password);
    }
}