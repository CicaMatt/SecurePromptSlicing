import java.sql.*;
    
    public class Post {
        private static final String URL = "jdbc:sqlite:messageboard.db";
        
        public void post(String username, String message) throws SQLException {
            Connection connection = DriverManager.getConnection(URL);
            PreparedStatement statement = connection.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?)");
            statement.setString(1, username);
            statement.setString(2, message);
            statement.executeUpdate();
        }
    
        public static void main(String[] args) throws SQLException {
            Post post = new Post();
            String username = "John";
            String message = "Hello from the other side!";
            post.post(username, message);
        }
    }