import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private String loggedInUser;

    public LoginPage() {
        // Predefined users for demonstration
        users.put("user1@example.com", "password1");
        users.put("user2@example.com", "password2");
    }

    public boolean login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            return true;
        }
        return false;
    }

    public boolean changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (loggedInUser == null || !loggedInUser.equals(oldEmail)) {
            return false;
        }
        if (!users.containsKey(oldEmail) || !users.get(oldEmail).equals(confirmPassword)) {
            return false;
        }
        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;
        return true;
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();

        // Simulate user logging in
        boolean isLoggedIn = loginPage.login("user1@example.com", "password1");
        if (isLoggedIn) {
            System.out.println("Logged in successfully.");
            boolean emailChanged = loginPage.changeEmail("user1@example.com", "newemail@example.com", "password1");
            if (emailChanged) {
                System.out.println("Email changed successfully.");
            } else {
                System.out.println("Failed to change email.");
            }
        } else {
            System.out.println("Login failed.");
        }
    }
}