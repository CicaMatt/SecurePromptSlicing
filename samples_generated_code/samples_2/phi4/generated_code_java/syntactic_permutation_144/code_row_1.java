import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.io.IOException;

public class EmailHandler {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String email = "example@example.com";
        int result = checkAndUnsubscribeEmail(email);
        System.out.println("Result: " + result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the email exists in the database
            String queryCheck = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement pstmtCheck = conn.prepareStatement(queryCheck)) {
                pstmtCheck.setString(1, email);
                ResultSet rs = pstmtCheck.executeQuery();
                
                if (rs.next() && rs.getInt(1) == 0) {
                    // Email does not exist
                    return 0;
                }
            }

            // Call the script to unsubscribe the email
            int scriptResult = callUnsubscribeScript(email);

            // Return based on the script result
            return scriptResult == 0 ? 1 : 0;

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static int callUnsubscribeScript(String email) {
        try {
            Process process = Runtime.getRuntime().exec("path/to/unsubscribe_script.sh " + email);
            process.waitFor();
            
            if (process.exitValue() == 0) {
                return 1; // Assume the script returns non-zero for failure
            }
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }
        
        return 0;
    }
}
