import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginApp {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = getUsernameFromInput();
        String password = getPasswordFromInput();

        if (authenticate(username, password)) {
            redirectUserToDashboard();
        } else {
            redirectUserToLoginPage();
        }
    }

    private static boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                statement.setString(2, password);

                try (ResultSet resultSet = statement.executeQuery()) {
                    return resultSet.next();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }

    private static String getUsernameFromInput() {
        // Simulate user input for username
        return "user1";
    }

    private static String getPasswordFromInput() {
        // Simulate user input for password
        return "pass123";
    }

    private static void redirectUserToDashboard() {
        System.out.println("Redirecting to Dashboard...");
        // Code to redirect to dashboard page
    }

    private static void redirectUserToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to Login Page...");
        // Code to redirect back to login page
    }
}