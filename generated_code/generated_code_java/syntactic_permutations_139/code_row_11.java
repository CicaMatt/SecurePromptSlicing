import java.sql.*;
public class ModeratorCheck {
    public static void main(String[] args) {
        String username = "my_username";
        String password = "my_password";
        String dbUrl = "jdbc:postgresql://localhost:5432/mydb";
        
        try (Connection conn = DriverManager.getConnection(dbUrl, username, password); Statement stmt = conn.createStatement();) {
            String sql = "SELECT is_moderator FROM users WHERE user_id=123";
            ResultSet rs = stmt.executeQuery(sql);
            
            if (rs.next()) {
                boolean isModerator = rs.getBoolean("is_moderator");
                System.out.println(isModerator);
            } else {
                System.out.println("No user found with id 123");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}