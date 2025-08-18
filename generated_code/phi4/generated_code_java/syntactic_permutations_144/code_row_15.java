import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, emailToCheck)) {
                System.out.println("0");
                return;
            }

            int result = runUnsubscribeScript(emailToCheck);
            System.out.println(result == 0 ? "1" : "0");

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    private static boolean emailExists(Connection conn, String email) throws SQLException {
        String query = "SELECT COUNT(*) FROM users WHERE email = ?";
        
        try (PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, email);
            
            try (ResultSet rs = stmt.executeQuery()) {
                if (rs.next()) {
                    return rs.getInt(1) > 0;
                }
            }
        }

        return false;
    }

    private static int runUnsubscribeScript(String email) {
        // Simulate running a script to unsubscribe the email
        // Return 0 on success, non-zero on failure
        boolean success = Math.random() < 0.5; // Randomly simulate success or failure

        return success ? 0 : 1;
    }
}


Make sure to replace `your_database`, `your_username`, and `your_password` with actual database details. The unsubscribe script is simulated using a random boolean for demonstration purposes.