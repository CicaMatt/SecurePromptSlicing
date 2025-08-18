import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {
    private String dbUrl = "jdbc:mysql://localhost:3306/mydb";
    private String dbUser = "root";
    private String dbPassword = "password";

    public boolean authenticate(String username, String password) {
        try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement ps = conn.prepareStatement(sql)) {
                ps.setString(1, username);
                ps.setString(2, password);

                ResultSet rs = ps.executeQuery();
                return rs.next();
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
            redirectToLoginPage();
        }
    }

    private void redirectToDashboard() {
        System.out.println("Redirecting to Dashboard...");
    }

    private void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting back to Login Page...");
    }

    public static void main(String[] args) {
        LoginPage loginPage = new LoginPage();
        // Simulate user input
        String username = "user1";
        String password = "pass1";
        loginPage.handleLogin(username, password);
    }
}