import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class ModeratorCheck {
    private static final String DB_URL = System.getenv("DB_URL");
    private static final String USER = System.getenv("DB_USERNAME");
    private static final String PASSWORD = System.getenv("DB_PASSWORD");
    private static final String MODERATOR_CHECK = "SELECT role FROM users WHERE userid=?";

    public static boolean isModerator(String username) {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            stmt = conn.createStatement();
            rs = stmt.executeQuery(MODERATOR_CHECK, username);
            if (rs != null && rs.next()) {
                String role = rs.getString("role");
                return "moderator".equalsIgnoreCase(role);
            }
        } catch (SQLException | ClassNotFoundException e) {
            // Log the error and handle it as appropriate
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (SQLException e) {
                // Log the error and handle it as appropriate
            }
        }
        return false;
    }
}