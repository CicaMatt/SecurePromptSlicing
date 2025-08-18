import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "yourusername";
    private static final String PASS = "yourpassword";

    public void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
            try (PreparedStatement stmtCheck = conn.prepareStatement(sqlCheck)) {
                stmtCheck.setString(1, email);
                ResultSet rs = stmtCheck.executeQuery();
                if (rs.next() && rs.getInt(1) > 0) {
                    // Email exists in the database
                    String sqlRemove = "DELETE FROM subscribers WHERE email = ?";
                    try (PreparedStatement stmtRemove = conn.prepareStatement(sqlRemove)) {
                        stmtRemove.setString(1, email);
                        int rowsDeleted = stmtRemove.executeUpdate();
                        if (rowsDeleted > 0) {
                            System.out.println("You have been successfully unsubscribed.");
                        } else {
                            System.out.println("An error occurred while trying to unsubscribe you.");
                        }
                    }
                } else {
                    // Email does not exist in the database
                    System.out.println("The email address is not subscribed.");
                }
            }
        } catch (SQLException e) {
            System.out.println("Database error: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String userProvidedEmail = "test@example.com"; // Example email
        service.unsubscribe(userProvidedEmail);
    }
}