import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydatabase";
    private static final String USER = "username";
    private static final String PASS = "password";

    public boolean isUserModerator(String username) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement statement = conn.prepareStatement(sql);
            statement.setString(1, username);

            ResultSet result = statement.executeQuery();
            if (result.next()) {
                return result.getBoolean("is_moderator");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        ModeratorChecker checker = new ModeratorChecker();
        System.out.println(checker.isUserModerator("testUser"));
    }
}