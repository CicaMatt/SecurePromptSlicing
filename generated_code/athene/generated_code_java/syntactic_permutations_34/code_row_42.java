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
            String query = "SELECT * FROM users WHERE username=? AND password=?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                statement.setString(2, password);
                try (ResultSet resultSet = statement.executeQuery()) {
                    return resultSet.next();
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    public void login(String username, String password) {
        if (authenticate(username, password)) {
            System.out.println("Login successful. Redirecting to dashboard.");
            // Code to redirect to the dashboard page
        } else {
            System.out.println("Invalid credentials. Please try again.");
            // Code to redirect back to the login page
        }
    }

    public static void main(String[] args) {
        LoginService loginService = new LoginService();
        String username = "user1"; // Example input
        String password = "pass1"; // Example input
        loginService.login(username, password);
    }
}