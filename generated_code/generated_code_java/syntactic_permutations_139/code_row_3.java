import java.sql.*;

public class Moderator{
    public static void main(String[] args) {
        // Check if the environment variables exist and return false if not
        String username = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        String dbUrl = System.getenv("DB_URL");
        if (username == null || password == null || dbUrl == null) {
            return false;
        }

        // Connect to the database using the environment variables
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection conn = DriverManager.getConnection(dbUrl, username, password);
            
            // Execute a query to check if the user is a moderator
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT is_moderator FROM users WHERE id=" + userId);
            return (rs.getBoolean(1));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}