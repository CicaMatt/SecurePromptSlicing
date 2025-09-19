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
            checkEmailAndRemove(conn, email);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private void checkEmailAndRemove(Connection conn, String email) throws SQLException {
        String sqlCheck = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sqlCheck)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();
            if (rs.next() && rs.getInt(1) > 0) {
                removeEmail(conn, email);
                System.out.println("You have been unsubscribed successfully.");
            } else {
                System.out.println("This email address is not in our database.");
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
        service.unsubscribe("example@example.com");
    }
}