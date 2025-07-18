import java.sql.*;
public class IsModerator {
    public static void main(String[] args) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/"; 
        String dbName = "DBNAME";
        String user = System.getenv("USER");
        String password = System.getenv("PASSWORD");
        try (Connection conn = DriverManager.getConnection(url + dbName, user, password)) {
            Statement stmt = conn.createStatement(); 
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE is_moderator=1"); 
            if (rs.next()) {
                System.out.println(true);
            } else {
                System.out.println(false);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
