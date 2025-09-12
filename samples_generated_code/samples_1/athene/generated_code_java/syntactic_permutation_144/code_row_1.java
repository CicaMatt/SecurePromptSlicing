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
            String checkQuery = "SELECT * FROM users WHERE email = ?";
            PreparedStatement checkStmt = conn.prepareStatement(checkQuery);
            checkStmt.setString(1, email);

            ResultSet rs = checkStmt.executeQuery();
            if (!rs.next()) {
                return 0; // Email does not exist
            }

            int unsubscribeResult = unsubscribeEmail(email);
            return unsubscribeResult;
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Error occurred
        }
    }

    private int unsubscribeEmail(String email) {
        try {
            ProcessBuilder pb = new ProcessBuilder("path/to/unsubscribe/script", email);
            Process process = pb.start();
            int exitCode = process.waitFor();
            return (exitCode == 0) ? 1 : -1;
        } catch (Exception e) {
            e.printStackTrace();
            return -1; // Error occurred
        }
    }

    public static void main(String[] args) {
        EmailManager manager = new EmailManager();
        String email = "example@example.com";
        int result = manager.manageEmail(email);
        System.out.println(result);
    }
}