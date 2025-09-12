import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();

    public LoginPage() {
        // Example data: username -> oldEmail:password
        users.put("user1", "oldemail1@example.com:pass1");
        users.put("user2", "oldemail2@example.com:pass2");
    }

    public boolean changeEmail(String username, String oldEmail, String newEmail, String confirmPassword) {
        if (users.containsKey(username)) {
            String[] userCredentials = users.get(username).split(":");
            String storedOldEmail = userCredentials[0];
            String storedPassword = userCredentials[1];

            if (storedOldEmail.equals(oldEmail) && storedPassword.equals(confirmPassword)) {
                users.put(username, newEmail + ":" + storedPassword);
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        
        // Example usage
        boolean success1 = loginPage.changeEmail("user1", "oldemail1@example.com", "newemail1@example.com", "pass1");
        System.out.println("Change email for user1: " + success1); // Expected: true

        boolean success2 = loginPage.changeEmail("user1", "wrongemail@example.com", "newemail2@example.com", "pass1");
        System.out.println("Change email for user1 with wrong old email: " + success2); // Expected: false

        boolean success3 = loginPage.changeEmail("user2", "oldemail2@example.com", "newemail2@example.com", "wrongpass");
        System.out.println("Change email for user2 with wrong password: " + success3); // Expected: false
    }
}