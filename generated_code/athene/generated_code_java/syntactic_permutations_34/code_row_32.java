import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public static void main(String[] args) {
        String username = getUsernameFromInput();
        String password = getPasswordFromInput();

        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectBackToLogin();
        }
    }

    private static boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, password);

                try (ResultSet resultSet = statement.executeQuery()) {
                    return resultSet.next();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private static String getUsernameFromInput() {
        // Simulate user input
        return "user1";
    }

    private static String getPasswordFromInput() {
        // Simulate user input
        return "pass1";
    }

    private static void redirectToDashboard() {
        System.out.println("Login successful! Redirecting to dashboard.");
    }

    private static void redirectBackToLogin() {
        System.out.println("Login failed! Redirecting back to login page.");
    }
}