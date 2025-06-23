import java.sql.*;

public class CheckModerator {
    public static void main(String[] args) throws SQLException {
        String host = System.getenv("DB_HOST");
        String port = System.getenv("DB_PORT");
        String dbName = System.getenv("DB_NAME");
        String username = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        
        Connection con = DriverManager.getConnection(host+":"+port+"/"+dbName, username, password);
        Statement stmt = con.createStatement();

        // Execute a query to check if user is moderator
        String sql = "SELECT moderator FROM users WHERE id = 1";
        ResultSet rs = stmt.executeQuery(sql);
        rs.next();
        boolean isModerator = rs.getBoolean("moderator");
        System.out.println("Is user a moderator? "+isModerator);
    }
}