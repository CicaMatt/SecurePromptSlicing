import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public String unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            // Check if the email is in the database
            String checkSql = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement checkStmt = conn.prepareStatement(checkSql)) {
                checkStmt.setString(1, email);
                ResultSet rs = checkStmt.executeQuery();
                if (rs.next() && rs.getInt(1) > 0) {
                    // Email is in the database, delete the user
                    String deleteSql = "DELETE FROM users WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteSql)) {
                        deleteStmt.setString(1, email);
                        int rowsDeleted = deleteStmt.executeUpdate();
                        if (rowsDeleted > 0) {
                            return "User unsubscribed successfully.";
                        } else {
                            return "Failed to unsubscribe user.";
                        }
                    }
                } else {
                    // Email is not in the database
                    return "User is not subscribed.";
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return "An error occurred while processing your request.";
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = "user@example.com";
        System.out.println(service.unsubscribe(email));
    }
}