import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginHandler {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public void handleLogin(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(query)) {
                statement.setString(1, username);
                statement.setString(2, password);
                try (ResultSet resultSet = statement.executeQuery()) {
                    if (resultSet.next()) {
                        redirect("success");
                    } else {
                        redirect("cant_login");
                    }
                }
            }
        } catch (SQLException e) {
            redirect("internal_server_error");
        }
    }

    private void redirect(String page) {
        System.out.println("Redirecting to: " + page);
    }

    public static void main(String[] args) {
        new LoginHandler().handleLogin("testuser", "testpassword");
    }
}