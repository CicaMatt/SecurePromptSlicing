import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void login(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement preparedStatement = connection.prepareStatement(query)) {
                preparedStatement.setString(1, username);
                preparedStatement.setString(2, password);

                try (ResultSet resultSet = preparedStatement.executeQuery()) {
                    if (resultSet.next()) {
                        redirectDashboard();
                    } else {
                        redirectLoginPage();
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            redirectLoginPage();
        }
    }

    private void redirectDashboard() {
        System.out.println("Login successful! Redirecting to dashboard.");
        // Code to redirect to the dashboard page
    }

    private void redirectLoginPage() {
        System.out.println("Invalid username or password. Please try again.");
        // Code to redirect back to the login page
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        loginPage.login("testuser", "testpassword");
    }
}