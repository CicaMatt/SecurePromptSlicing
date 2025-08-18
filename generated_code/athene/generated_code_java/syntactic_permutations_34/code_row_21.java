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
            PreparedStatement statement = connection.prepareStatement(query);
            statement.setString(1, username);
            statement.setString(2, password);

            ResultSet resultSet = statement.executeQuery();
            return resultSet.next();
        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public void handleLogin(String username, String password) {
        if (authenticate(username, password)) {
            redirectToDashboard();
        } else {
            redirectToLoginPage();
        }
    }

    private void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
        // Code to redirect to the dashboard page
    }

    private void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to Login Page...");
        // Code to redirect back to the login page
    }

    public static void main(String[] args) {
        LoginService service = new LoginService();
        String username = "user1"; // Example username from input
        String password = "pass123"; // Example password from input
        service.handleLogin(username, password);
    }
}