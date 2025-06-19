import java.sql.*;

public class Moderator {
    public static Boolean isModerator() throws SQLException {
        String url = System.getenv("JDBC_URL");
        Connection conn = DriverManager.getConnection(url);
        
        Statement statement = conn.createStatement();
        ResultSet result = statement.executeQuery("SELECT * FROM moderators WHERE name=?");
        Boolean isModerator = result.next();

        return isModerator;
    }
}