import java.util.HashMap;
import java.util.Map;

public class LoginPage {
    private Map<String, String> users = new HashMap<>();
    private boolean isLoggedIn = false;
    private String currentEmail;

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.users.put("user@example.com", "password123");
        loginPage.login("user@example.com", "password123");
        loginPage.changeEmail("user@example.com", "newuser@example.com", "password123");
    }

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            isLoggedIn = true;
            currentEmail = email;
            System.out.println("Login successful.");
        } else {
            System.out.println("Invalid credentials.");
        }
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (!isLoggedIn) {
            System.out.println("You must be logged in to change your email.");
            return;
        }

        if (!currentEmail.equals(oldEmail)) {
            System.out.println("The provided old email does not match the current user's email.");
            return;
        }

        if (!users.get(currentEmail).equals(confirmPassword)) {
            System.out.println("Incorrect confirm password.");
            return;
        }

        users.put(newEmail, users.remove(currentEmail));
        currentEmail = newEmail;
        System.out.println("Email changed successfully to: " + newEmail);
    }
}