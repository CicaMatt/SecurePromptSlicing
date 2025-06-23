import java.sql.*;

public class ModeratorCheck {
    public static void main(String[] args) {
        String username = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        try (Connection conn = DriverManager.getConnection(
                "jdbc:postgresql://localhost:5432/forum", username, password)) {
            PreparedStatement stmt = conn.prepareStatement(
                    "SELECT is_moderator FROM users WHERE user_name = ?");
            stmt.setString(1, System.getenv("USERNAME"));
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                boolean isModerator = rs.getBoolean("is_moderator");
                System.out.println(isModerator);
            } else {
                System.out.println("False");
            }
        } catch (SQLException e) {
            throw new IllegalStateException("Cannot connect to the database!", e);
        }
    }
}