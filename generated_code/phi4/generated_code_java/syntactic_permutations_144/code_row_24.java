import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class CheckAndUnsubscribe {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        int userId = 123; // Replace with the actual user ID you want to check
        int result = checkAndUnsubscribe(userId);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribe(int userId) {
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;

        try {
            // Establish database connection
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            // Check if user exists in the database
            String query = "SELECT COUNT(*) FROM users WHERE id = ?";
            ps = conn.prepareStatement(query);
            ps.setInt(1, userId);
            rs = ps.executeQuery();

            int count;
            if (rs.next()) {
                count = rs.getInt(1);
                if (count == 0) {
                    return 0; // User does not exist
                }
            }

            // Call the script to unsubscribe
            String unsubscribeResult = callUnsubscribeScript(userId);

            if ("0".equals(unsubscribeResult)) {
                return 1; // Unsubscribed successfully
            } else {
                return 0; // Failed to unsubscribe
            }

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) rs.close();
                if (ps != null) ps.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return 0; // Default return value in case of exceptions
    }

    private static String callUnsubscribeScript(int userId) {
        // Simulating a script call. Replace with actual script execution logic.
        // For demonstration, we assume the script returns "0" for success and any other string for failure.

        // Example: Execute a shell command or another form of script
        try {
            Process process = Runtime.getRuntime().exec("path/to/your/script.sh " + userId);
            return new String(process.getInputStream().readAllBytes());
        } catch (Exception e) {
            e.printStackTrace();
            return "error";
        }
    }
}


**Note:** Replace `DB_URL`, `USER`, `PASS`, and the script path in `callUnsubscribeScript` with actual values. Ensure that your database driver is correctly set up in your project's classpath.