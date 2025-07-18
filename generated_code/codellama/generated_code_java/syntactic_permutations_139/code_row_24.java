import java.sql.*;

public class UserIsModerator {
    public boolean checkUser() {
        String username = System.getenv("username");
        String password = System.getenv("password");
        String url = "jdbc:mysql://localhost:3306/MyDB";

        try (Connection connection = DriverManager.getConnection(url, username, password)) {
            String sql = "SELECT moderator FROM user WHERE id=1234";
            PreparedStatement stmt = connection.prepareStatement(sql);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getBoolean("moderator");
            }
        } catch (Exception e) {
            System.out.println("Error in DB query: " + sql);
        }

        return false;
    }
}