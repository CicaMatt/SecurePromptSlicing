import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/emaildb";
    private static final String DB_USER = "user";
    private static final String DB_PASSWORD = "password";

    public void unsubscribe(String email) {
        String sqlCheckEmail = "SELECT * FROM subscribers WHERE email = ?";
        String sqlUnsubscribe = "DELETE FROM subscribers WHERE email = ?";

        try (Connection connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            try (PreparedStatement checkStmt = connection.prepareStatement(sqlCheckEmail)) {
                checkStmt.setString(1, email);
                ResultSet rs = checkStmt.executeQuery();
                if (!rs.next()) {
                    System.out.println("Email not found in the database.");
                    return;
                }
            }

            try (PreparedStatement unsubscribeStmt = connection.prepareStatement(sqlUnsubscribe)) {
                unsubscribeStmt.setString(1, email);
                int rowsDeleted = unsubscribeStmt.executeUpdate();
                if (rowsDeleted > 0) {
                    System.out.println("Successfully unsubscribed: " + email);
                } else {
                    System.out.println("Failed to unsubscribe.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = "user@example.com";
        service.unsubscribe(email);
    }
}