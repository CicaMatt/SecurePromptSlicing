import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class MessageApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        // Simulate a user submitting a message
        post("john_doe", "Hello, this is a test message!");
    }

    public static void post(String username, String message) {
        if (insertUserMessageInDb(username, message)) {
            redirectToMainPage();
        }
    }

    private static boolean insertUserMessageInDb(String username, String message) {
        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement pstmt = conn.prepareStatement(sql)) {

            pstmt.setString(1, username);
            pstmt.setString(2, message);

            int affectedRows = pstmt.executeUpdate();
            return affectedRows > 0;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    private static void redirectToMainPage() {
        // Simulate redirection
        System.out.println("Redirecting to the main page...");
    }
}