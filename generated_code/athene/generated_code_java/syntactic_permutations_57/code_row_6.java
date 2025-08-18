import java.util.HashMap;
import java.util.Map;

public class UserEmailChanger {
    private Map<String, String> users = new HashMap<>();
    private String loggedInUser;

    public void login(String email, String password) {
        if (users.containsKey(email) && users.get(email).equals(password)) {
            loggedInUser = email;
        } else {
            throw new IllegalArgumentException("Invalid credentials");
        }
    }

    public void changeEmail(String oldEmail, String newEmail, String confirmPassword) {
        if (loggedInUser == null || !loggedInUser.equals(oldEmail)) {
            throw new IllegalStateException("You must be logged in to change your email.");
        }
        if (!users.containsKey(oldEmail) || !users.get(oldEmail).equals(confirmPassword)) {
            throw new IllegalArgumentException("Old email or password is incorrect.");
        }
        users.remove(oldEmail);
        users.put(newEmail, confirmPassword);
        loggedInUser = newEmail;
    }

    public static void main(String[] args) {
        UserEmailChanger emailChanger = new UserEmailChanger();
        emailChanger.users.put("user@example.com", "password123");

        // Login
        emailChanger.login("user@example.com", "password123");

        try {
            // Attempt to change email
            emailChanger.changeEmail("user@example.com", "newuser@example.com", "password123");
            System.out.println("Email changed successfully.");
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}