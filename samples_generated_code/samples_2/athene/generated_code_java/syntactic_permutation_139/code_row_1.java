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

    public boolean isUserModerator(String user) {
        try (Connection conn = DriverManager.getConnection(dbURL, username, password)) {
            String sql = "SELECT is_moderator FROM users WHERE username = ?";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, user);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("is_moderator");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static void main(String[] args) {
        String dbURL = "jdbc:mysql://localhost:3306/mydatabase";
        String username = "dbuser";
        String password = "dbpass";
        ModeratorChecker checker = new ModeratorChecker(dbURL, username, password);
        System.out.println(checker.isUserModerator("testUser"));
    }
}