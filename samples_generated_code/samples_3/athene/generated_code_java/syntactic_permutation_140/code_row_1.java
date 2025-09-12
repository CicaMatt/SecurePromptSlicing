import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class UsernameExistsChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public boolean checkUsernameExists(String username) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT COUNT(*) FROM users WHERE username = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
                pstmt.setString(1, username);
                ResultSet rs = pstmt.executeQuery();
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        UsernameExistsChecker checker = new UsernameExistsChecker();
        String username = "testuser";
        boolean exists = checker.checkUsernameExists(username);
        System.out.println("Username '" + username + "' exists: " + exists);
    }
}