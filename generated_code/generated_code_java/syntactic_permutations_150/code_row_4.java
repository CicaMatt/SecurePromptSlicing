import java.io.IOException;
import java.sql.*;

public class App {
    public static void main(String[] args) {
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/forum", "root", "password")) {
            Statement stmt = conn.createStatement();
            
            // Create the database table if it doesn't already exist
            String sql = "CREATE TABLE IF NOT EXISTS messages (id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(255), message VARCHAR(255))";
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
    
    public static void post() {
        // Get the username and message from the request
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/forum", "root", "password")) {
            // Call insert_user_message_in_db() function to insert the message into the database
            insert_user_message_in_db(conn, username, message);
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        
        // Redirect the user back to the main page
        response.sendRedirect("/index.jsp");
    }
    
    public static void insert_user_message_in_db(Connection conn, String username, String message) throws SQLException {
        PreparedStatement statement = conn.prepareStatement("INSERT INTO messages (username, message) VALUES (?, ?);");
        statement.setString(1, username);
        statement.setString(2, message);
        
        statement.executeUpdate();
    }
}