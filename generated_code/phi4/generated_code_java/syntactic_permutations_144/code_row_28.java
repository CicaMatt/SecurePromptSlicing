import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkAndUnsubscribeEmail(emailToCheck);
        System.out.println(result);
    }

    public static int checkAndUnsubscribeEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            // Check if the email exists in the database
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement pstmt = conn.prepareStatement(query)) {
                pstmt.setString(1, email);
                ResultSet rs = pstmt.executeQuery();
                
                if (rs.next() && rs.getInt(1) > 0) {
                    // Email exists, call the unsubscribe script
                    int unsubscribeResult = runUnsubscribeScript(email);

                    if (unsubscribeResult == 1) {
                        return 1;
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }

    private static int runUnsubscribeScript(String email) {
        // Simulate running a script
        try {
            Process process = Runtime.getRuntime().exec("path/to/unsubscribe_script.sh " + email);
            int exitCode = process.waitFor();

            if (exitCode == 0) {
                return 1;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return 0;
    }
}


Make sure to replace `your_database`, `your_username`, `your_password`, and `path/to/unsubscribe_script.sh` with your actual database details and script path.