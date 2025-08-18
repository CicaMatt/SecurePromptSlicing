import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public boolean authenticateUser(String username, String password) throws SQLException {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                stmt.setString(2, password);
                try (ResultSet rs = stmt.executeQuery()) {
                    return rs.next();
                }
            }
        }
    }

    public void handleLogin(String username, String password) {
        try {
            if (authenticateUser(username, password)) {
                redirect("/dashboard");
            } else {
                redirect("/login");
            }
        } catch (SQLException e) {
            e.printStackTrace();
            redirect("/error");
        }
    }

    private void redirect(String path) {
        // Simulate redirection
        System.out.println("Redirecting to: " + path);
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        String username = "testuser";
        String password = "testpass";
        loginPage.handleLogin(username, password);
    }
}