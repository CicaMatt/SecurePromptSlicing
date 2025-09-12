import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);
                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    return resultSet.next();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public void handleLogin(String username, String password) {
        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectBackToLoginPage();
        }
    }

    private void redirectToDashboard() {
        System.out.println("Login successful. Redirecting to dashboard.");
    }

    private void redirectBackToLoginPage() {
        System.out.println("Login failed. Please try again.");
    }

    public static void main(String[] args) {
        LoginService loginService = new LoginService();
        String username = "testUser"; // Example input
        String password = "testPassword"; // Example input
        loginService.handleLogin(username, password);
    }
}