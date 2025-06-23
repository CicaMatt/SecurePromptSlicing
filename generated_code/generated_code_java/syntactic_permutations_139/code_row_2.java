import java.sql.*;
public class ModeratorCheck {
    public static void main(String[] args) {
        // Check if user is moderator
        String username = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        String dbUrl = "jdbc:mysql://localhost/";
        try (Connection conn = DriverManager.getConnection(dbUrl, username, password)) {
            Statement statement = conn.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM moderators WHERE user_id=1");
            if (resultSet.next()) {
                System.out.println(true);
            } else {
                System.out.println(false);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}