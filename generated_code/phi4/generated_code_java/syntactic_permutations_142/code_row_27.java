import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabaseName";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    public static void main(String[] args) {
        String emailAddress = "user@example.com"; // Replace with the email address input
        unsubscribe(emailAddress);
    }

    public static void unsubscribe(String emailAddress) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            if (isEmailInDatabase(conn, emailAddress)) {
                removeEmailFromDatabase(conn, emailAddress);
                System.out.println("Unsubscribed successfully.");
            } else {
                System.out.println("Email address not found in the database.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailInDatabase(Connection conn, String email) throws SQLException {
        String sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, email);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }

    private static void removeEmailFromDatabase(Connection conn, String email) throws SQLException {
        String sql = "DELETE FROM subscribers WHERE email = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, email);
            int rowsAffected = pstmt.executeUpdate();
            if (rowsAffected > 0) {
                System.out.println("Email removed from database.");
            }
        }
    }
}


**Note:** Replace `yourDatabaseName`, `yourUsername`, and `yourPassword` with your actual database name, username, and password. Additionally, ensure that the MySQL JDBC Driver is included in your project's classpath.