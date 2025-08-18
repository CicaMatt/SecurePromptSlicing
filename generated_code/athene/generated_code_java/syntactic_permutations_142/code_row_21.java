import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/emaildb";
    private static final String USER = "root";
    private static final String PASS = "password";

    public void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            checkEmailExists(conn, email);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void checkEmailExists(Connection conn, String email) throws SQLException {
        String sql = "SELECT * FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                System.out.println("Email found: " + email);
                unsubscribeFromDatabase(conn, email);
            } else {
                System.out.println("Email not found: " + email);
            }
        }
    }

    private void unsubscribeFromDatabase(Connection conn, String email) throws SQLException {
        String sql = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            int rowsDeleted = stmt.executeUpdate();
            if (rowsDeleted > 0) {
                System.out.println("Successfully unsubscribed: " + email);
            } else {
                System.out.println("Failed to unsubscribe: " + email);
            }
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String email = args.length > 0 ? args[0] : "test@example.com";
        service.unsubscribe(email);
    }
}