import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginSystem {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String DB_USER = "root";
    private static final String DB_PASSWORD = "password";

    public void handleLogin(String username, String password) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                redirectToDashboard();
            } else {
                redirectToLoginPage();
            }
        } catch (Exception e) {
            e.printStackTrace();
            redirectToLoginPage();
        }
    }

    private void redirectToDashboard() {
        System.out.println("Login successful. Redirecting to dashboard.");
    }

    private void redirectToLoginPage() {
        System.out.println("Invalid credentials. Redirecting to login page.");
    }

    public static void main(String[] args) {
        LoginSystem loginSystem = new LoginSystem();
        String username = "testuser";
        String password = "testpassword";
        loginSystem.handleLogin(username, password);
    }
}