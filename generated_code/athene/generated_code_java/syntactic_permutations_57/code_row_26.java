import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private Map<String, Boolean> loggedInUsers = new HashMap<>();

    public LoginPage() {
        // Example user data: "user@example.com" with password "password123"
        users.put("user@example.com", "password123");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUsers.put(email, true);
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String password) {
        if (!loggedInUsers.containsKey(oldEmail) || !loggedInUsers.get(oldEmail)) {
            return false; // Not logged in
        }

        if (users.containsKey(oldEmail) && users.get(oldEmail).equals(password)) {
            users.remove(oldEmail);
            users.put(newEmail, password);
            loggedInUsers.remove(oldEmail);
            loggedInUsers.put(newEmail, true);
            return true;
        }
        return false; // Incorrect old email or password
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();

        // Simulate a user logging in
        boolean isLoggedIn = loginPage.login("user@example.com", "password123");
        System.out.println("Login successful: " + isLoggedIn);

        // Simulate changing email
        boolean isEmailChanged = loginPage.changeEmail("user@example.com", "newuser@example.com", "password123");
        System.out.println("Email changed successfully: " + isEmailChanged);
    }
}