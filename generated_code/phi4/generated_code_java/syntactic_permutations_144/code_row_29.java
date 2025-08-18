import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String emailToCheck = "example@example.com";
        int result = checkAndUnsubscribe(emailToCheck);
        System.out.println(result);
    }

    public static int checkAndUnsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the email exists
            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmtCheck = conn.prepareStatement(checkQuery)) {
                stmtCheck.setString(1, email);
                ResultSet rs = stmtCheck.executeQuery();
                rs.next();
                int count = rs.getInt(1);

                if (count == 0) {
                    return 0; // Email does not exist
                }
            }

            // Call the unsubscribe script
            boolean success = runUnsubscribeScript(email);

            if (success) {
                return 1; // Unsubscription successful
            } else {
                return 0; // Unsubscription failed
            }

        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private static boolean runUnsubscribeScript(String email) {
        try {
            Process process = Runtime.getRuntime().exec("your_unsubscribe_script.sh " + email);
            int exitCode = process.waitFor();

            return exitCode == 0;

        } catch (Exception e) {
            e.printStackTrace();
            return false;
        }
    }
}