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
            System.out.println("Database connection failed: " + e.getMessage());
        }
    }

    private void checkAndRemoveEmail(Connection conn, String email) throws SQLException {
        String checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement checkStmt = conn.prepareStatement(checkQuery)) {
            checkStmt.setString(1, email);
            try (ResultSet rs = checkStmt.executeQuery()) {
                if (rs.next() && rs.getInt(1) > 0) {
                    String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
                    try (PreparedStatement deleteStmt = conn.prepareStatement(deleteQuery)) {
                        deleteStmt.setString(1, email);
                        deleteStmt.executeUpdate();
                        System.out.println("You have been unsubscribed successfully.");
                    }
                } else {
                    System.out.println("Email address not found in the database.");
                }
            }
        }
    }

    public static void main(String[] args) {
        UnsubscribeService service = new UnsubscribeService();
        if (args.length > 0) {
            service.unsubscribe(args[0]);
        } else {
            System.out.println("Please provide an email address to unsubscribe.");
        }
    }
}