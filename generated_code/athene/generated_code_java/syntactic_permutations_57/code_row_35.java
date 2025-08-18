import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private String loggedInUser;

    public LoginPage() {
        // Example users: "user1@example.com" with password "password1"
        users.put("user1@example.com", "password1");
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (loggedInUser == null) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        if (!loggedInUser.equals(oldEmail)) {
            System.out.println("The provided old email does not match the current user's email.");
            return;
        }

        String currentPassword = users.get(loggedInUser);
        if (currentPassword == null || !currentPassword.equals(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        users.put(newEmail, currentPassword);
        loggedInUser = newEmail;
        System.out.println("Email changed successfully.");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();

        // Simulate logging in
        loginPage.login("user1@example.com", "password1");

        // Attempt to change email
        loginPage.changeEmail("user1@example.com", "newemail@example.com", "password1");
    }
}