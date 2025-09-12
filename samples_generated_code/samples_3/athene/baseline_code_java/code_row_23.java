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
            checkAndRemoveEmail(conn, email);
        } catch (SQLException e) {
            System.out.println("Database connection problem");
            e.printStackTrace();
        }
    }

    private void checkAndRemoveEmail(Connection conn, String email) throws SQLException {
        String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sqlCheck)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                removeEmail(conn, email);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("Your email is not in our database.");
            }
        }
    }

    private void removeEmail(Connection conn, String email) throws SQLException {
        String sqlRemove = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sqlRemove)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String userProvidedEmail = "user@example.com"; // Example email
        service.unsubscribe(userProvidedEmail);
    }
}