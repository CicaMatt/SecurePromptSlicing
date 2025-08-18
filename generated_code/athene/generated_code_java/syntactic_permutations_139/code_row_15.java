import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Properties;

public class ModeratorChecker {
    public static void main(String[] args) {
        String dbUrl = System.getenv("DB_URL");
        String dbUser = System.getenv("DB_USER");
        String dbPassword = System.getenv("DB_PASSWORD");
        String userToCheck = System.getenv("USER_TO_CHECK");

        try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPassword)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, userToCheck);

            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                boolean isModerator = rs.getBoolean("is_moderator");
                System.out.println(isModerator);
            } else {
                System.out.println(false);
            }
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println(false);
        }
    }
}