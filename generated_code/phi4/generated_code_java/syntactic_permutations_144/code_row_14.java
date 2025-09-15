import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailUnsubscriber {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "username";
    private static final String PASS = "password";

    public static void main(String[] args) {
        String emailToCheck = "test@example.com";
        int result = checkAndUnsubscribe(emailToCheck);
        System.out.println(result == 1 ? "Success" : "Failure");
    }

    public static int checkAndUnsubscribe(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {

            // Check if the email exists in the database
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (!rs.next() || rs.getInt(1) == 0) {
                    return 0; // Email does not exist
                }
            }

            // Call the unsubscribe script
            String[] command = {"path/to/unsubscribe_script.sh", email};
            Process process = Runtime.getRuntime().exec(command);
            int exitCode = process.waitFor();
            
            if (exitCode == 0) {
                return 1; // Unsubscribed successfully
            } else {
                return 0; // Failed to unsubscribe
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }
}
