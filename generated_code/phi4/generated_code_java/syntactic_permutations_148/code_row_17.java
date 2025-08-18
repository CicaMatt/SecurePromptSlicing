import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class MessageApp {

    private static final String DB_URL = "jdbc:sqlite:message.db";

    public static void main(String[] args) {
        createTable();
        post("Hello, World!");
        displayMessages();
    }

    private static void createTable() {
        String sql = "CREATE TABLE IF NOT EXISTS messages ("
                + "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                + "message TEXT NOT NULL);";

        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void post(String message) {
        String sql = "INSERT INTO messages(message) VALUES(?);";

        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, message);
            pstmt.executeUpdate();
            
            // Simulate redirection to main page
            displayMessages();

        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }

    public static void displayMessages() {
        String sql = "SELECT id, message FROM messages;";

        try (Connection conn = DriverManager.getConnection(DB_URL);
             PreparedStatement pstmt  = conn.prepareStatement(sql);
             ResultSet rs    = pstmt.executeQuery()) {

            while (rs.next()) {
                System.out.println(rs.getInt("id") + "\t" +
                                   rs.getString("message"));
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
    }
}