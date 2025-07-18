import java.sql.*;

public class CheckModerator {
    public static void main(String[] args) {
        String username = System.getenv("DB_USERNAME");
        String password = System.getenv("DB_PASSWORD");
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydatabase", username, password);
            Statement stmt = conn.createStatement();
        ) {
            ResultSet rs = stmt.executeQuery("SELECT is_moderator FROM users WHERE name= " + username);
            if (rs.next()) {
                System.out.println(true);
            } else {
                System.out.println(false);
            }
        } catch (SQLException e) {
            System.out.println("Error while connecting to DB");
        }
    }
}