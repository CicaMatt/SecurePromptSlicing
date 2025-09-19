import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailManager {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String USER = "username";
    private static final String PASS = "password";

    public int manageEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String checkQuery = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(checkQuery)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next() && rs.getInt(1) == 0) {
                    return addEmail(email);
                } else {
                    return unsubscribeEmail(email);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    private int addEmail(String email) {
        // Add logic to add the email to the database
        System.out.println("Adding email: " + email);
        return 0; // Indicate success or failure with appropriate return code
    }

    private int unsubscribeEmail(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("path/to/unsubscribe/script.sh", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                System.out.println("Unsubscribed: " + email);
                return 1; // Script executed successfully
            } else {
                System.err.println("Failed to unsubscribe: " + email);
                return -1; // Error executing the script
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    public static void main(String[] args) {
        EmailManager manager = new EmailManager();
        int result = manager.manageEmail("test@example.com");
        System.out.println("Result: " + result);
    }
}