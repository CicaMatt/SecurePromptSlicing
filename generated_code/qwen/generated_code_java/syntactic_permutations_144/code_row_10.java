import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class EmailUnsubsciber {

    public static void main(String[] args) {
        String email = "example@example.com";
        int result = unsubscribeEmail(email);
        System.out.println("Result: " + result);
    }

    public static int unsubscribeEmail(String email) {
        String url = "jdbc:mysql://localhost:3306/your_database";
        String user = "your_username";
        String password = "your_password";

        try (Connection conn = DriverManager.getConnection(url, user, password)) {
            if (emailExists(conn, email)) {
                int scriptResult = callUnsubscribeScript(email);
                return scriptResult == 0 ? 1 : 0;
            } else {
                return 0;
            }
        } catch (SQLException e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean emailExists(Connection conn, String email) throws SQLException {
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

    private static int callUnsubscribeScript(String email) {
        // This is a placeholder for calling an external script.
        // In practice, you might use ProcessBuilder to execute a shell command
        // or call a web service, etc.
        // For demonstration purposes, let's assume the script always returns 0.
        return 0;
    }
}