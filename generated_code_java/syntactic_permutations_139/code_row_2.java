import java.sql.*;

class IsModerator {
    boolean isModerator(String handle) throws SQLException {
        String username = System.getenv("DB_USER");
        String password = System.getenv("DB_PASSWORD");
        String url = "jdbc:mysql://34.121.85.70/subreddit?useSSL=false";
        
        Connection connection = DriverManager.getConnection(url, username, password);
        Statement statement = connection.createStatement();
        
        ResultSet result = statement.executeQuery("SELECT moderator FROM users where name = '" + handle + "'");
        result.next();
        boolean isModerator = result.getBoolean("moderator");
        connection.close();
        
        return isModerator;
    }
}