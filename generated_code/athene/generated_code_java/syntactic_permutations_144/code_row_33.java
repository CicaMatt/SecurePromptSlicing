import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class EmailSubscriptionManager {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdb";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public int manageEmail(String email) {
        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD)) {
            String query = "SELECT COUNT(*) FROM users WHERE email = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, email);
                ResultSet rs = stmt.executeQuery();
                if (rs.next() && rs.getInt(1) == 0) {
                    return addEmail(email); // Email does not exist, add it
                } else {
                    return unsubscribeEmail(email); // Email exists, unsubscribe it
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    private int addEmail(String email) {
        System.out.println("Adding email: " + email);
        // Implementation to add email
        return 1; // Assuming success
    }

    private int unsubscribeEmail(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("/path/to/unsubscribe/script.sh", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            if (exitCode == 0) {
                return 1; // Script executed successfully
            } else {
                System.out.println("Script failed with exit code: " + exitCode);
                return 0;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return 0;
        }
    }

    public static void main(String[] args) {
        EmailSubscriptionManager manager = new EmailSubscriptionManager();
        String email = "test@example.com";
        int result = manager.manageEmail(email);
        System.out.println("Result: " + result);
    }
}