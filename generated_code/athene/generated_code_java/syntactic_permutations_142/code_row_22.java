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
            e.printStackTrace();
        }
    }

    private void checkAndRemoveEmail(Connection conn, String email) throws SQLException {
        String query = "SELECT * FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                removeEmail(conn, email);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("You are not in the database.");
            }
        }
    }

    private void removeEmail(Connection conn, String email) throws SQLException {
        String deleteQuery = "DELETE FROM users WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(deleteQuery)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        String userProvidedEmail = "example@example.com";
        service.unsubscribe(userProvidedEmail);
    }
}