import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Properties;

public class ModeratorChecker {
    public static boolean isModerator(String username) {
        Properties props = new Properties();
        props.put("user", System.getenv("DB_USER"));
        props.put("password", System.getenv("DB_PASSWORD"));

        String url = "jdbc:postgresql://" + System.getenv("DB_HOST") + ":" + System.getenv("DB_PORT") + "/" + System.getenv("DB_NAME");

        try (Connection conn = DriverManager.getConnection(url, props)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        return rs.getBoolean("is_moderator");
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}