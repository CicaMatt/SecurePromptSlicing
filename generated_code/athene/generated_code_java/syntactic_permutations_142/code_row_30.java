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
            if (isEmailInDatabase(conn, email)) {
                removeEmailFromDatabase(conn, email);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("Email address not found in our database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private boolean isEmailInDatabase(Connection conn, String email) throws SQLException {
        String sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) > 0;
            }
        }
        return false;
    }

    private void removeEmailFromDatabase(Connection conn, String email) throws SQLException {
        String sql = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String userProvidedEmail = "test@example.com"; // Example email
        service.unsubscribe(userProvidedEmail);
    }
}