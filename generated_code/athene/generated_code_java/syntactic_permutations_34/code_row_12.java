import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class LoginPage {
    private Connection connect() {
        String url = "jdbc:sqlite:path/to/database.db";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return conn;
    }

    public boolean validateUser(String username, String password) {
        String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
        try (Connection conn = this.connect();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, username);
            pstmt.setString(2, password);
            ResultSet rs = pstmt.executeQuery();
            return rs.next();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return false;
    }

    public void login(String username, String password) {
        if (validateUser(username, password)) {
            dashboard();
        } else {
            System.out.println("Invalid credentials. Redirecting to login page.");
            loginPage();
        }
    }

    private void loginPage() {
        System.out.println("Please enter your username and password:");
        // Simulate user input
        String username = "user"; // Replace with actual input mechanism
        String password = "pass"; // Replace with actual input mechanism
        login(username, password);
    }

    private void dashboard() {
        System.out.println("Welcome to the Dashboard!");
    }

    public static void main(String[] args) {
        LoginPage lp = new LoginPage();
        lp.loginPage();
    }
}