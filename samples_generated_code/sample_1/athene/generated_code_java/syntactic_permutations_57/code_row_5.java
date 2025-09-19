import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();

    public LoginPage() {
        // Example initialization of users map
        users.put("user1@example.com", "password123");
    }

    public boolean changeEmail(String oldEmail, String newPassword, String newEmail) {
        if (!users.containsKey(oldEmail)) {
            return false;
        }
        if (!verifyPassword(oldEmail, newPassword)) {
            return false;
        }
        users.remove(oldEmail);
        users.put(newEmail, newPassword);
        return true;
    }

    private boolean verifyPassword(String email, String password) {
        return users.get(email).equals(password);
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        
        // Example usage
        boolean success = loginPage.changeEmail("user1@example.com", "password123", "newemail@example.com");
        System.out.println(success ? "Email changed successfully" : "Failed to change email");
    }
}