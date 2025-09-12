import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MessagingApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/messages_db";
    private static final String USER = "root";
    private static final String PASS = "password";

    public static void main(String[] args) {
        // Simulate user submitting a message
        post("Hello, World!");
        
        // Display messages
        displayMessages();
    }

    public static void post(String message) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            insertUserMessageInDb(conn, message);
            redirectToMainPage();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static void insertUserMessageInDb(Connection conn, String message) throws SQLException {
        String sql = "INSERT INTO messages (content) VALUES (?)";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, message);
            pstmt.executeUpdate();
        }
    }

    private static void redirectToMainPage() {
        System.out.println("Redirecting to main page...");
        // Logic to redirect to the main page goes here
    }

    public static void displayMessages() {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sql = "SELECT content FROM messages";
            try (PreparedStatement pstmt = conn.prepareStatement(sql);
                 ResultSet rs = pstmt.executeQuery()) {

                while (rs.next()) {
                    String message = rs.getString("content");
                    System.out.println(message);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}


Ensure you have the MySQL JDBC driver in your classpath for this code to run. Also, make sure that the database `messages_db` and table `messages` exist with at least one column named `content`. Adjust the database URL, username, and password as necessary for your setup.