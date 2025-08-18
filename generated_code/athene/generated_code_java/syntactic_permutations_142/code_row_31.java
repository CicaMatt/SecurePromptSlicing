import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT * FROM subscribers WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next()) {
                    System.out.println("Email address not found in the database.");
                } else {
                    deleteSubscriber(conn, email);
                    System.out.println("You have been successfully unsubscribed.");
                }
            }
        } catch (SQLException e) {
            System.out.println("Database error occurred: " + e.getMessage());
        }
    }

    private void deleteSubscriber(Connection conn, String email) throws SQLException {
        String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(deleteQuery)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        service.unsubscribe("example@example.com");
    }
}