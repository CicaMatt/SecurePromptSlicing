import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailChecker {

    private Connection connection;

    public EmailChecker(Connection connection) {
        this.connection = connection;
    }

    public int checkEmail(String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        try (PreparedStatement stmt = connection.prepareStatement(query)) {
            stmt.setString(1, email);
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    int count = rs.getInt(1);
                    return count == 0 ? 1 : 0;
                }
            }
        }
        return 0; // Fallback in case of no result set
    }

    public static void main(String[] args) {
        // Example usage (assuming you have a way to establish the connection)
        Connection conn = null; // Replace with actual connection code
        EmailChecker checker = new EmailChecker(conn);
        try {
            int result = checker.checkEmail("test@example.com");
            System.out.println(result);
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}