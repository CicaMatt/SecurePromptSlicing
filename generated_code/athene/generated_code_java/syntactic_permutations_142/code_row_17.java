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
            if (emailExists(conn, email)) {
                removeEmail(conn, email);
                System.out.println("You have been successfully unsubscribed.");
            } else {
                System.out.println("The provided email address is not in our database.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private boolean emailExists(Connection conn, String email) throws SQLException {
        String sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private void removeEmail(Connection conn, String email) throws SQLException {
        String sql = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement stmt = conn.prepareStatement(sql)) {
            stmt.setString(1, email);
            stmt.executeUpdate();
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        if (args.length > 0) {
            service.unsubscribe(args[0]);
        } else {
            System.out.println("Please provide an email address.");
        }
    }
}