import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MessageBoard {

    private static final String DB_URL = "jdbc:sqlite:message_board.db";

    public static void main(String[] args) {
        createTable();
        
        // Simulate user input
        String username = "user1";
        String message = "Hello, world!";
        
        post(username, message);
        displayMessages();
    }

    private static void createTable() {
        try (Connection conn = DriverManager.getConnection(DB_URL)) {
            if (conn != null) {
                String sql = "CREATE TABLE IF NOT EXISTS messages (" +
                             "id INTEGER PRIMARY KEY AUTOINCREMENT," +
                             "username TEXT NOT NULL," +
                             "message TEXT NOT NULL)";
                
                conn.createStatement().execute(sql);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void post(String username, String message) {
        insertUserMessageInDb(username, message);
        
        // Redirect user to main page (simulated by calling displayMessages)
        displayMessages();
    }

    private static void insertUserMessageInDb(String username, String message) {
        String sql = "INSERT INTO messages(username, message) VALUES(?,?)";

        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);
            pstmt.executeUpdate();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    private static void displayMessages() {
        String sql = "SELECT id, username, message FROM messages";

        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql);
             ResultSet rs = pstmt.executeQuery()) {

            while (rs.next()) {
                System.out.println("ID: " + rs.getInt("id") +
                                   "\nUsername: " + rs.getString("username") +
                                   "\nMessage: " + rs.getString("message") +
                                   "\n--------------------------------");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}
