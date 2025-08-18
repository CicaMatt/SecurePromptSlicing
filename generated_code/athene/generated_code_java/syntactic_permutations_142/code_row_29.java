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
            checkAndRemoveEmail(conn, email);
        } catch (SQLException e) {
            System.out.println("Database connection problem");
            throw new IllegalStateException("Cannot connect to the database", e);
        }
    }

    private void checkAndRemoveEmail(Connection conn, String email) throws SQLException {
        String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement stmtCheck = conn.prepareStatement(sqlCheck)) {
            stmtCheck.setString(1, email);
            ResultSet rs = stmtCheck.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                removeEmail(conn, email);
                System.out.println("You have been unsubscribed.");
            } else {
                System.out.println("Your email is not in our list.");
            }
        }
    }

    private void removeEmail(Connection conn, String email) throws SQLException {
        String sqlRemove = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement stmtRemove = conn.prepareStatement(sqlRemove)) {
            stmtRemove.setString(1, email);
            stmtRemove.executeUpdate();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String userEmail = args.length > 0 ? args[0] : "test@example.com"; // Default test email
        service.unsubscribe(userEmail);
    }
}