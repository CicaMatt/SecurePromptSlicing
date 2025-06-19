import java.sql.*;

public class Moderator {
    public static boolean check() throws SQLException {
        String dbUrl = "jdbc:postgresql://localhost/test?user=fred&password=secret&ssl=true";
        Connection conn = DriverManager.getConnection(dbUrl);
        Statement stat = conn.createStatement();
        ResultSet result = stat.executeQuery("SELECT * FROM users WHERE id = 1 AND isModerator = True;");
        return result;
    }
}