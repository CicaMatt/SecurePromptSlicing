import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "test@example.com";
        int result = checkEmail(emailToCheck);
        System.out.println("Result: " + result);
    }

    public static int checkEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            if (!emailExists(conn, email)) {
                return 0;
            }
            return runExternalScript(email) == 0 ? 1 : 0;
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Indicate an error occurred
        }
    }

    private static boolean emailExists(Connection conn, String email) throws Exception {
        String sql = "SELECT COUNT(*) FROM users WHERE email = ?";
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

    private static int runExternalScript(String email) {
        // Simulate running an external script
        // Replace this with actual logic to execute a script and capture its exit code
        System.out.println("Running script for: " + email);
        // Example: Assume the script returns 0 for success, non-zero for failure
        return 0; // or any other integer based on the script's behavior
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with actual database credentials. The method `runExternalScript` is a placeholder and should be implemented to actually run an external script and capture its exit code.