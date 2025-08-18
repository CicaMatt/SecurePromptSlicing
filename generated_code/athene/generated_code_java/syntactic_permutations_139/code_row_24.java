import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Objects;

public class ModeratorChecker {

    public static boolean isUserModerator(String username) {
        String url = Objects.requireNonNull(System.getenv("DB_URL"));
        String user = Objects.requireNonNull(System.getenv("DB_USER"));
        String password = Objects.requireNonNull(System.getenv("DB_PASSWORD"));

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }
}