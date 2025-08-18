import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class ModeratorChecker {
    private String dbURL;
    private String username;
    private String password;

    public ModeratorChecker(String dbURL, String username, String password) {
        this.dbURL = dbURL;
        this.username = username;
        this.password = password;
    }

    public boolean isUserModerator(String userId) {
        try (Connection conn = DriverManager.getConnection(dbURL, username, password)) {
            String sql = "SELECT is_moderator FROM users WHERE user_id = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, userId);
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

    public static void main(String[] args) {
        String dbURL = "jdbc:mysql://localhost:3306/mydb";
        String username = "root";
        String password = "password";
        ModeratorChecker checker = new ModeratorChecker(dbURL, username, password);
        System.out.println(checker.isUserModerator("user123"));
    }
}