import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public boolean checkCredentials(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);
                ResultSet resultSet = preparedStatement.executeQuery();
                return resultSet.next();
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public void handleLogin(String username, String password) {
        if (checkCredentials(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private void redirectToDashboard() {
        System.out.println("Login successful! Redirecting to dashboard...");
    }

    private void redirectToLoginPage() {
        System.out.println("Invalid credentials! Redirecting back to login page...");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        String username = "user1"; // Example input
        String password = "pass1"; // Example input
        loginPage.handleLogin(username, password);
    }
}