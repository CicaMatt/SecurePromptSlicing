import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Objects;

public class ModeratorChecker {
    public boolean isUserModerator(String username) {
        String url = Objects.requireNonNullElse(System.getenv("DB_URL"), "");
        String user = Objects.requireNonNullElse(System.getenv("DB_USER"), "");
        String password = Objects.requireNonNullElse(System.getenv("DB_PASSWORD"), "");

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                if (rs.next()) {
                    return rs.getBoolean("is_moderator");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        System.out.println(checker.isUserModerator(args[0]));
    }
}