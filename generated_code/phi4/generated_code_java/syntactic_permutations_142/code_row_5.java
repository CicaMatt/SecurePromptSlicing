import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class UnsubscribeService {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database_name";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        String emailToRemove = "user@example.com"; // Replace with the actual email address
        unsubscribe(emailToRemove);
    }

    public static void unsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!isEmailInDatabase(conn, email)) {
                System.out.println("The email address is not in the database.");
                return;
            }
            
            String deleteQuery = "DELETE FROM subscribers WHERE email = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(deleteQuery)) {
                pstmt.setString(1, email);
                int rowsAffected = pstmt.executeUpdate();
                
                if (rowsAffected > 0) {
                    System.out.println("The email address has been successfully removed.");
                } else {
                    System.out.println("An error occurred while removing the email address.");
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean isEmailInDatabase(Connection conn, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        try (PreparedStatement pstmt = conn.prepareStatement(query)) {
            pstmt.setString(1, email);
            try (ResultSet rs = pstmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }
        return false;
    }
}


**Note**: Replace `your_database_name`, `your_db_user`, and `your_db_password` with your actual database name, username, and password. Also, ensure you have the MySQL JDBC driver in your classpath or build path.