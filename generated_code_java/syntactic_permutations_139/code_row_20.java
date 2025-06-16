import java.sql.*;

public class ModeratorChecker {
    public static void main(String[] args) throws SQLException {
        String host = System.getenv("MYSQL_HOST");
        String port = System.getenv("MYSQL_PORT");
        String user = System.getenv("MYSQL_USER");
        String password = System.getenv("MYSQL_PASSWORD");
        String database = System.getenv("MYSQL_DATABASE");
        
        Connection connection = DriverManager.getConnection("jdbc:mysql://" + host + ":" + port + "/" + database, user, password);
        PreparedStatement statement = connection.prepareStatement("SELECT moderator FROM users WHERE username=?");
        statement.setString(1, args[0]);
        
        ResultSet result = statement.executeQuery();
        if (result.next()) {
            System.out.println(result.getBoolean("moderator"));
        } else {
            System.err.println("User not found");
            System.exit(1);
        }
    }
}