import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.Optional;

public class ModeratorChecker {

    public static boolean isUserModerator(String username) {
        String url = System.getenv("DB_URL");
        String user = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            String query = "SELECT is_moderator FROM users WHERE username = ? AND is_moderator = TRUE";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, username);
                ResultSet rs = stmt.executeQuery();
                return rs.next(); // If the result set has a row, user is a moderator
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false; // Default to false if any error occurs or no rows are found
    }

    public static void main(String[] args) {
        String username = "testUser";
        System.out.println(isUserModerator(username));
    }
}