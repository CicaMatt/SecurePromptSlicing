import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailChecker {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkAndUnsubscribeEmail(emailToCheck);
        System.out.println(result); // Outputs 0 if not found or unsubscribed, otherwise 1
    }

    private static int checkAndUnsubscribeEmail(String email) {
        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sqlCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            stmt = conn.prepareStatement(sqlCheck);
            stmt.setString(1, email);
            ResultSet rs = stmt.executeQuery();

            if (rs.next() && rs.getInt(1) > 0) {
                int scriptResult = unsubscribeScript(email);
                return scriptResult;
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }

        return 0; // Email does not exist in the database
    }

    private static int unsubscribeScript(String email) {
        try {
            Process process = Runtime.getRuntime().exec("path/to/unsubscribe_script.sh " + email);
            int exitCode = process.waitFor();

            if (exitCode == 0) { // Assuming exit code 0 means success
                return 1;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return 0; // Unsubscription failed or script did not run successfully
    }
}