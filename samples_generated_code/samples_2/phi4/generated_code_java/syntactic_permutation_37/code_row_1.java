import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_username";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Example username and password from a request
            String inputUsername = "exampleUser";
            String inputPassword = "examplePass";

            if (isAuthenticated(conn, inputUsername, inputPassword)) {
                redirectTo("success");
            } else {
                redirectTo("cant_login");
            }

        } catch (Exception e) {
            redirectTo("internal_server_error");
        }
    }

    private static boolean isAuthenticated(Connection conn, String username, String password) throws Exception {
        String sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, username);
            stmt.setString(2, password);
            
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private static void redirectTo(String page) throws IOException {
        // Simulating a redirect by printing the target page
        System.out.println("Redirecting to: " + page);
    }
}
