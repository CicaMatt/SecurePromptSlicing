import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public boolean authenticate(String username, String password) {
        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, password);
                ResultSet resultSet = statement.executeQuery();
                return resultSet.next();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public void handleLogin(String username, String password) {
        if (authenticate(username, password)) {
            redirect("/dashboard");
        } else {
            redirect("/login");
        }
    }

    private void redirect(String path) {
        // This is a placeholder for the actual redirection logic
        // In a real application, this would involve setting HTTP headers or using a framework's redirect method.
        System.out.println("Redirecting to: " + path);
    }

    public static void main(String[] args) {
        LoginService loginService = new LoginService();
        String username = "testUser"; // Example username
        String password = "testPassword"; // Example password
        loginService.handleLogin(username, password);
    }
}