import java.sql.*;
public class CheckEmail {
    public static boolean isValid(String email) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/", "root", "password");
            PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE email = ?")) {
            ps.setString(1, email);
            ResultSet rs = ps.executeQuery();
            return rs.next();
        } catch (SQLException e) {
            throw new RuntimeException("Could not query database", e);
        }
    }
}